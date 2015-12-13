#!/usr/bin/env bash

set -eo pipefail

cd $PEBBLE
. .env/bin/activate
cd -

set -u

waf build
pebble install --logs --emulator chalk