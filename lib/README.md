# featherweight-lib

This folder contains the results of the builds from [kernel](../kernel).

To properly link these files from a built application follow the directions below for your respective target.

## Linux RT

1. Copy the .so file for your target to `/usr/lib`
1. Make a link of the LabVIEW RT lib to `/usr/lib` by running the following command:

```
ln -sf /usr/local/natinst/labview/liblvrt.so.15.0 /usr/lib/
```

- Note that this currently only works for LabVIEW 2015. Newer targets will need to build specifically for that version.

## Windows

The appropriate .dll for your LabVIEW bitness will be automatically statically linked in builds.
