#!/usr/bin/make -f
# -*- mode: makefile; indent-tabs-mode: t -*- vim:noet:ts=4

all: debug

release:
	xcodebuild -project laipinyin.xcodeproj -configuration Release build
	rm -f build/laipinyin.app
	cd build ; ln -s Release/laipinyin.app laipinyin.app

debug:
	xcodebuild -project laipinyin.xcodeproj -configuration Debug build
	rm -f build/laipinyin.app
	cd build ; ln -s Debug/laipinyin.app laipinyin.app

install:
	rm -rf "/Library/Input Methods/laipinyin.app"
	cp -R build/Debug/laipinyin.app "/Library/Input Methods"

install-release:
	rm -rf "/Library/Input Methods/laipinyin.app"
	cp -R build/Release/laipinyin.app "/Library/Input Methods"

clean:
	rm -rf build

