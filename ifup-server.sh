#!/bin/sh
export INTERFACE=`cat env/INTERFACE`
export TUN_ADDR=`cat env/TUN_ADDR`
export GATEWAY=`cat env/GATEWAY`
export PTP=`cat env/PTP`
ip link del $INTERFACE
(
  sleep 4
  ip addr add $TUN_ADDR peer $PTP/32 dev $INTERFACE scope link
  ip addr add $GATEWAY/32 dev $INTERFACE scope global
  ip link set dev $INTERFACE up
  ifconfig $INTERFACE mtu 1024
) &
ping -c 1 -I $INTERFACE $PTP -r -w 5 &
exec ./tun $INTERFACE ./tunserver
