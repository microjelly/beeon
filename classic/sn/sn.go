package main

import (
	"bytes"
	"flag"
	"fmt"
	"io"
	"math/rand"
	"os"
	"strings"
	"time"

	"github.com/marcinbor85/gohex"
)

var (
	snLetters        = []rune("ABCDEF0123456789")
	snStock   string = "BEE#-##-#######"
)

func main() {

	stockSN := snBytes(snStock)

	inhFile := flag.String("inh", "beeon-classic.hex", "input hex file")
	insFile := flag.String("ins", "beeon-sn.txt", "input sn(s) file")
	mkFile := flag.Bool("mk", false, "make-file : create random sn(s)")
	mkPfx := flag.String("mk-p", "#-##", "make-file-prefix : string to add befoer random sn(s)")
	mkAmount := flag.Int("mk-a", 1024, "make-file-amount : how many random sn(s) to make")
	flag.Parse()

	// make the sn(s) if being asked
	if *mkFile {
		rand.Seed(time.Now().UnixNano())
		made := 0
		failLimit := 20
		randStrings := make([]string, *mkAmount)
		for made < *mkAmount {
			newS := strings.ToUpper(randSeq(7))
			if contains(randStrings, newS) {
				failLimit--
				if failLimit < 0 {
					break
				}
				continue
			}
			randStrings[made] = newS
			made++
		}

		for _, v := range randStrings {
			fmt.Printf("%s-%s\n", *mkPfx, v)
		}
		os.Exit(0)
	}

	// else patch hex and dump to stdout
	sFile, err := os.OpenFile(*insFile, os.O_RDWR, 0666)
	if err != nil {
		panic(err)
	}
	defer sFile.Close()
	line, err := popLine(sFile)
	if err != nil {
		panic(err)
	}
	if string(line) == "" {
		panic(fmt.Errorf("no sn(s) %v", line))
	}
	newSN := snBytes(strings.Trim(string(line), "\n"))

	hFile, err := os.Open(*inhFile)
	if err != nil {
		panic(err)
	}
	defer hFile.Close()

	mem := gohex.NewMemory()
	err = mem.ParseIntelHex(hFile)
	if err != nil {
		panic(err)
	}

	rawBytes := mem.ToBinary(0x0000, 8192, 0x00)
	indexSN := bytes.Index(rawBytes, stockSN)

	// patch in new SN +6 (BxExEx<>)
	mem.SetBinary(uint32(indexSN+6), newSN)

	mem.DumpIntelHex(os.Stdout, 16)
}

func randSeq(n int) string {
	b := make([]rune, n)
	for i := range b {
		b[i] = snLetters[rand.Intn(len(snLetters))]
	}
	return string(b)
}

func contains(a []string, x string) bool {
	for _, n := range a {
		if x == n {
			return true
		}
	}
	return false
}

func snBytes(i string) []byte {

	bytes := make([]byte, len(i)*2)
	r := []byte(i)
	idx := 0
	for _, rx := range r {
		bytes[idx] = rx
		idx = idx + 2
	}
	return bytes

}

func snString(i string) string {
	o := "{ \"SN\": ["
	r := []rune(i)
	c := ""
	for _, rx := range r {
		o = fmt.Sprintf("%s%s-%d, 0", o, c, rx)
		c = ", "
	}
	return o + " ] }"
}

func popLine(f *os.File) ([]byte, error) {
	fi, err := f.Stat()
	if err != nil {
		return nil, err
	}
	buf := bytes.NewBuffer(make([]byte, 0, fi.Size()))

	_, err = f.Seek(0, io.SeekStart)
	if err != nil {
		return nil, err
	}
	_, err = io.Copy(buf, f)
	if err != nil {
		return nil, err
	}

	line, err := buf.ReadBytes('\n')
	if err != nil && err != io.EOF {
		return nil, err
	}

	_, err = f.Seek(0, io.SeekStart)
	if err != nil {
		return nil, err
	}
	nw, err := io.Copy(f, buf)
	if err != nil {
		return nil, err
	}
	err = f.Truncate(nw)
	if err != nil {
		return nil, err
	}
	err = f.Sync()
	if err != nil {
		return nil, err
	}

	_, err = f.Seek(0, io.SeekStart)
	if err != nil {
		return nil, err
	}
	return line, nil
}
