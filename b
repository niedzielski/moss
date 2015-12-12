#!/usr/bin/env bash

set -eo pipefail

cd $PEBBLE
. .env/bin/activate
cd -

waf build
pebble install --logs --emulator chalk