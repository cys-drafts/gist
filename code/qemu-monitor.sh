#!/bin/bash
# $0 <libvirt domain>

domain=$1

while read -p "> " cmd; do
	virsh qemu-monitor-command ${domain} --hmp ${cmd}
done

