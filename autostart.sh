#!/bin/bash

function run {
 if ! pgrep $1 ;
  then
    $@&
  fi
}

run "xrandr --output eDP1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output DP1 --off --output HDMI1 --off --output HDMI2 --off --output VIRTUAL1 --off"
run "xrandr --output eDP1 --mode 1920x1080 --pos 0x0 --rotate normal --output DP1 --off --output HDMI1 --primary --mode 3840x2160 --pos 1920x0 --rotate normal --output HDMI2 --off --output VIRTUAL1 --off"
run "xrandr --output eDP1 --off --output DP1 --off --output HDMI1 --primary --mode 3840x2160 --pos 1920x0 --rotate normal --output HDMI2 --off --output VIRTUAL1 --off"

#run "dex $HOME/.config/autostart/arcolinux-welcome-app.desktop"
run "nm-applet"
run "pamac-tray"
run "variety"
run "xfce4-power-manager"
run "volumeicon"
run "blueberry-tray"
run "ssh-agent -s"

run "/usr/lib/xfce4/notifyd/xfce4-notifyd"
run "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1"

picom -b --config ~/.config/picom/picom.conf &
run "numlockx on"
run slstatus &
#run dwmblocks &
#sxhkd -c ~/.config/sxhkd/sxhkdrc &
#you can set wallpapers in themes as well
#feh --bg-fill /usr/share/backgrounds/arcolinux/arco-wallpaper.jpg &
