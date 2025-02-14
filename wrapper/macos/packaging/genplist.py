#!/usr/bin/env python

import plistlib, hashlib, os, sys

dir = "../../../data"
filenames = [ "lm_sc.t3g.le", "pydict_sc.bin.le" ]
files = []
plist_file = "laipinyinDataFiles.xml"

def sha256(file):
    s = hashlib.sha256()

    s.update(open(file, "rb").read())
    return s.hexdigest()

if len(sys.argv) > 1:
    plist_file = sys.argv[1]

for filename in filenames:
    path = os.path.join(dir, filename)
    print "Processing %s..." % filename

    file = {}

    file["Name"] = filename
    file["URL"] = "http://laipinyin.googlecode.com/files/%s" % filename
    file["Size"] = int(os.path.getsize(path))
    file["SHA256"] = sha256(path)

    files.append(file)

plistlib.writePlist(files, plist_file)

print "Done, written to %s." % plist_file

# -*- indent-tabs-mode: nil -*- vim:et:ts=4
