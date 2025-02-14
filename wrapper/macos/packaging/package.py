#!/usr/bin/env python3
# Package laipinyin for release

import sys, os, subprocess, time, plistlib

try:
    from jinja2 import Environment, FileSystemLoader
except:
    print("Install jinja2 first.")
    sys.exit(1)

env = Environment(loader=FileSystemLoader('.'))
plist = plistlib.readPlist("../build/laipinyin.app/Contents/Info.plist")

url_base = "http://laipinyin.googlecode.com/files/"
xml_url_base = "http://release.laipinyin.googlecode.com/git/"
appcast_url = xml_url_base + "laipinyinAppcast.xml"

pack_proj = "laipinyin/laipinyin.packproj"
pkg = "laipinyin/build/laipinyin.pkg"
resource_dir = "../build/laipinyin.app/Contents/Resources"

version = plist["CFBundleVersion"]
releasenotes_url = xml_url_base + "laipinyinReleaseNotes.xml"

zip = "laipinyin-MacOS-%s.zip" % version
file_url = url_base + zip

priv_key = "%s/.ssh/dsa_priv.pem" % os.path.expanduser('~')
date = time.strftime("%a, %d %b %Y %H:%M:%S %z")
appcast_template = 'appcast.template.xml'
appcast = "laipinyin_appcast.xml"

if len(sys.argv) > 1:
    priv_key = sys.argv[1]

def remove_if_exists(file):
    if os.path.isfile(file):
        os.remove(file)

print("[PACK] Remove temporary files...")

#remove_if_exists("%s/lm_sc.t3g" % resource_dir)
#remove_if_exists("%s/pydict_sc.bin" % resource_dir)

print("[PACK] Building %s..." % pkg)

os.system("freeze -v %s" % pack_proj)

print("[PACK] Compressing %s..." % zip)
os.chdir("laipinyin/build")
os.system("zip -y -r ../../%s laipinyin.pkg" % zip)
os.chdir("../..")

print("[PACK] Signing %s..." % zip)
signed = subprocess.getoutput('openssl dgst -sha1 -binary < "%s" | openssl dgst -dss1 -sign "%s" | openssl enc -base64' % (zip, priv_key))

print("[PACK] Generating %s..." % appcast)
template = env.get_template(appcast_template)

output = open(appcast, "w")

output.write(template.render(link=appcast_url,
        releaseNotesLink=releasenotes_url,
        url=file_url,
        date=date,
        version=version,
        length=os.path.getsize(zip),
        signed=signed))

output.close()

print("Done! Please:\n  1. Publish %s to %s\n  2. Publish %s to %s\n  3. Update the release note for version %s at %s." % (appcast, appcast_url, zip, file_url, version, releasenotes_url))

# -*- indent-tabs-mode: nil -*- vim:et:ts=4
