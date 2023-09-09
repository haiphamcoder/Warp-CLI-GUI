PWD := $(shell pwd)
TARGET := 'Warp-Cloudflare-GUI'

default:
	mkdir -p $(PWD)/bin
	cp -r $(PWD)/assets $(PWD)/bin/
	cp -r $(PWD)/styles $(PWD)/bin/
	cp ui.glade $(PWD)/bin/
	gcc -o $(PWD)/bin/$(TARGET) $(PWD)/main.c -pthread `pkg-config --cflags --libs gtk+-3.0`
clean:
	rm -rf $(PWD)/bin
run: default
	$(PWD)/bin/$(TARGET)
install: default
	mkdir -p /opt/warp-cloudflare-gui/
	cp -r $(PWD)/assets /opt/warp-cloudflare-gui/
	cp -r $(PWD)/styles /opt/warp-cloudflare-gui/
	cp ui.glade /opt/warp-cloudflare-gui/
	cp $(PWD)/bin/$(TARGET) /opt/warp-cloudflare-gui/ 
	echo "[Desktop Entry]\nName=Warp Cloudflare\nVersion=1.0\nComment=A guil app base on warp-cli for linux\nExec=/opt/warp-cloudflare-gui/Warp-Cloudflare-GUI\nIcon=/opt/warp-cloudflare-gui/icons/warp_gui.png\nType=Application\nTerminal=false\nCategories=Network;"> /usr/share/applications/warp-cloudflare-gui.desktop
	chmod +x /usr/share/applications/warp-cloudflare-gui.desktop
uninstall:
	rm -rf /opt/warp-cloudflare-gui
	rm /usr/share/applications/warp-cloudflare-gui.desktop