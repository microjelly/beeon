#!/bin/bash
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

mkdir -p ${DAPPER_OUTPUT}
if [ -e ${DIR}/$1 ]; then
    ${DIR}/"$@"
else
    exec "$@"
fi

chown -R $DAPPER_UID:$DAPPER_GID ${DAPPER_OUTPUT}