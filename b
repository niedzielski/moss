#!/usr/bin/env bash

set -eo pipefail

cd $PEBBLE
. .env/bin/activate
cd -

set -u

pebble build
pebble install --logs --emulator chalk # --phone 192.168.1.12
