#!/bin/bash
sudo cp `dirname $0`/libsys_monitor.so /usr/lib/dde-dock/plugins/libsys_monitor.so
killall dde-dock