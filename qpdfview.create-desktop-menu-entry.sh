#!/bin/sh

appimage="qpdfview-0.4.17beta1.glibc2.14-x86_64.AppImage"
uniquename="${appimage}-$(date +%s)"  # seconds since 1970-01-01 00:00:00 UTC, good enough for this purpose
desktopfile="$HOME/.local/share/applications/$uniquename.desktop"
iconfile="$HOME/.local/share/icons/$uniquename.png"

mkdir -p "$HOME/.local/share/applications"
mkdir -p "$HOME/.local/share/icons"

cat <<EOF> "$desktopfile"
[Desktop Entry]
Type=Application
TryExec=$PWD/$appimage
Exec="$PWD/$appimage" %F
Name=qpdfview
Icon=$iconfile
GenericName=tabbed document viewer
Comment=A tabbed document viewer using Qt and the Poppler library.
Categories=Viewer;Office;
Keywords=viewer;document;presentation;pdf;ps;djvu;
MimeType=application/pdf;application/x-pdf;text/pdf;text/x-pdf;image/pdf;image/x-pdf;image/vnd.djvu;image/x-djvu;
Terminal=false
Actions=RemoveDesktopintegration;

[Desktop Action RemoveDesktopintegration]
Name=Remove desktop integration
Exec=rm -f "$desktopfile"; rm -f "$iconfile"; xdg-desktop-menu forceupdate
EOF

cat <<EOF | base64 -d > "$iconfile"
iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAABmJLR0QA/wD/AP+gvaeTAAALN0lE
QVRoge2aW2xbx5nHf+fCmyiRlEjdKMlW7FiW7fgiqXHVetvY2Li20cQ24CLbLNruBSmKPvVhgYWf
Fvu0D/uWl7xsXRgGWiAIik0cN07W8dbGdhdKYsNpFNmW4l1bsqXoRlEUzcu5zEwfKCqURFK0lX3r
BxBnOGc48//PN99lZgh/lj/LpkSr9OKNN9540efzvaFpWkjXdQzDQNMKzaWUCCGQUqKUWimXqxdC
VGxT+nFdd1U7pVSxLpvP5//hwoUL/14Op1mJgMfj+eVLL720tampqaaZUErVXP8kbdPpNGfPnj0P
PBkBKWU4FAoxMzODbdtomoaUkkAggG3bACsaqVauVleLRKNRXNcNVnpfkUBxNorqLKq3WC62KQKr
VF7bXy1Eim11XV/1/YkISClXBiw3u7XOfjXApe9KQZYbo5JsqIHSztZ2/HWQqNZmUwTKdVQO+NjY
WM2AapFdu3Y9UfsNl9BaQGufO3fu/NqNea32N2UD1cBrmsbdu3erAqtUv2vXrg1toBapyYirPUtV
Xsn4NmsD/68aqBao1gKodWaL7nNtf+Xkib3QWrf62WefPRG4Wtr19fXV3LaqBkpJVNPCQ60bDaiv
e0xnNImOxqOFEEuZEArtidZ0l7q/btK+tkBWzZ36fTkGti0Qb9qNAtqjdxka9ZDJV8wCKkqlKF5O
9EovhBAr5WQyieM4VQdp8OdoDndh6s14jRaa6uNEgpmqQEVuCenkKxKoxYgrEihdPrlcblU6XU4D
lmtiuUuAi1IOtrtE3vaUBVf4nSKfeMDi6HWUa6+zr9Lypr1Qe3s7dXV1ZDKZiq7ycS7M5+NTbG8b
QkPjwZzGYqat0Fd+CTs1hSFyNDb40aRiIbmAyNsgXdL3PyHc8xerSJY+N20Duq5jWVbFATRNQyqN
B7PtTC1YaOhYrhf3cYKgNcW3nu+jtbUXXddxXbcwsGmilGJubo6hoSHmp+/gb91ZdnKemkDRA1TL
RldHUx3LCYBS2DOfc+zQAdra9pNKpbh1Z5zhBylml2w0oDnk48C2MN3tEU6ePMn8/DyXr1zHaWta
N+6ml1ARaCXwMZ8Clm0GSD0c5gcnj2LbNlc+GuXN/5rC4/XSEm0g5A+Qy2UYnljkD6NJpOvwo8Nb
+eaeDv76ldO88847pFIpwuHw5gmUi6DlZn7if++v1MncND959RSZTJZfvj/G6FSWb+/bwkBPC62N
AVwhcFxBOmvxf5NJbj+Y48LvJ/jjgxR/970eTp06xdtvv82xY8fw+XxlJ7NUqrrRjbLM4jObzZLL
5cim5zn+l9/CdV3OfTDGRMLhB4d3cvrQNp5pa8DrMVa8mddjsq2jie8ceIbnnmnk7mSG8/8xhm3b
HDlyhBs3bmzOjRbjQC2pci6fI5fL0hR0icfjfDQyxe1HGV440MHebVEUqrDAlCp80NDQUFLiM3We
7WyiJezhxr0kN+5MEovFsG2bVCr19AQqLaFS+UoDGaz8EgN9+0in0/zm+kO2t4fY0x3FcQWW7ZKz
HCzbxXFdXNctHJ8oEFKQydkoJelsbeDX18ZJpVL09fUxOjpaFTzUkMytBVuunMvniAQkLS0tPJxJ
IaRkS2sDUkos20HoOpqmUApcIXBdie0KbMfFdSWzC2mUAlMHV2k8mk2xrbOZmZmZquCrEli7H6hU
VsDJw3t49OghpmkyPJ6ivaWBLW1hTFPHY+gYOujL7T2mhjAlPmngdw3SWYdIg4/6oA+hwBYw8mCR
7ngU0zRXjnCemEBpLjQ6Okp7ezvBYHAdiee/8Q00TSOZXEAIwVzKprkpTH19EK/Xi8fUMXUNQ9f4
6qeFMyZXKtJOhq1dHdiuxHYleeFjNpXGdV3q6urIZrNVCVS1gaLE43Fisdgq4GvLxcCj64WobDsC
V0qEUMtrfdmQAQ0FmsZS1kFKhcfQMI0CSQBd1xBCrIrclaQmGwiFQus6KgIfHh4GwLIsDMOgJeLj
0/EUUzMePFoDHn0ZnAa6Vgh4riOYSS7xOGsjlIYjwRHgSo1MTtLd5kcpRT6fp66u7ukIFA9by4Eu
yuTk5ErE9Hg8KKXY3x3hP4cTZB1FMm0T9Bs0N0XwGhqarsHyyd6WYBhHKPKOwHIVedvFchUf3b3D
Dwe3oes66XSaQCDwdATKGfHa7z6fD7/fj23bdHR0MD09TWc8jqkp8rYgYyscKbg/cZs6vwevUfA0
Hh2EBEcWZt0WIJRO4rGDz1Q0N9aztLS0zuaeikA1KdVQa2srt27dYseOHfz4yBbOXZ3g+OB2pITm
5haijSF8Hh2voWMYGkqBLRS2K7EcSd4WXL8ywmsvduH3+7l69SqDg4MbYqgpF6okuq7j9XoRQmAY
BpFIhImJCQ4+183n4ymGhif5bl8X07OzpJdSmHrBDgq2qiHUsiYU/GF4nsEdEfb1dDI1NUU+n6ej
o2NDAjV5oUrLyDRNAoEAwWCQYDDI/v37uXnzJtlslp8c28PuuI/f/fc9DF8Dre0dtHV0Eu/cSryr
m3jXVuKdW/HUx7g+vMA3exp59cXduK7L3NwciUSCTz75ZEMCVePARhpQSuH3+1cMTdM0jh8/zgcf
fMDRo0f52+8fYP+dCS5cvc/1WxO0N/oJBjxoGujeAPcnFwl44GfHutm7o5N8Po9lWSSTSdra2hga
GuLRo0dPT6AUaKkWUqkU4+Pj6LrOwsLCurjQ2dnJe++9x6FDhxjY083eHXFmEik+vTfH7KKFrkFz
2ODVb++iJRrGNE0mJiZIJBLYto0QgsePHxOLxUgkEggh9MOHD5vXrl1bFxQqmvgrr7ySPHfuXCSf
z6+k1q7rYpoms7Mz9Pbu4q233lrdWekWU0oWFxdpbW1l7969xGIxvF7vqsBXnO2PP/6YdDqNZVls
376dubk5IpEIk5OTeDwehBBcuXLl967rnrp48WK6JgJnzpxJnj9/fh2BL74YW/YOGq5biKSglp9F
z1RI3AAS8/OMfTHGwkISv9+P3+9f2WOnUikCgQD9/f10dXXx7rvvMjs7SzweJ51OEw6HmZ6eRgiB
3+/nww8//CKdTh+5dOnSZBGnUYnA7t27z54+fdrvOM7KEpJSsrCQwDQNrHyOsdExYrGmgseSEqUk
ShZvGQufQMBHczRGOr1EKBxm9+49NDU18eyzz9Lf309vby/hcBilFD09PczNzTEyMkJXVxfpdJpI
JIJt22QyGXp7e6OZTObvY7HY5Xv37s3ABhcclQ5uU6klRkdHicWi3L59B1h2u1+1Wt4iayglyefz
ZLNZfP4AxVvPcrstpRRHjx6lpaWFixcvcvDgQTKZDJFIBMMwSCaTDAwMROrr628Ap99///33KhLQ
dd2yLItQKLRSJ6VE1w1CoQb27dtbuOMVAlH6XFOnlMQ0DcLhMK5biBcbSX9/P42NjZw7d47BwUFs
2yYYDGIYBvPz87zwwgue+vr6d3VdP1LNBn7huu6/GoaxKiT39Owwf/rT10zHcWoiUHqxfevTP8qh
oY+qJ/glIqXUgsGg9+WXX9Y0rZChtre309XVhc/n4+zZs/9TNdE4ceKET9f1Velgd3f3awcPPv8v
pmmYuq6vLAUpBFKpEgIKJSVSCaQo1I9PPLx27dq1H8ZisZpJOI7jCYfDb506deq7oVBo5WbH7/fz
+uuvT1S1gcuXL1uAtab6t8mFv3ouGot2eTym7vP5Cht0JRFCIoVEyAIBKcXy3w0klpXPXbp0+Z8S
iUQKWH+iW0UGBgZefPPNN//tzJkzfxMMBhFC8OWXX6qRkZELT3eVWDB+L1XccBlxgJpnvpycOHHi
5z09Pf8cjUbrbt68+Svbtv/xTwUfUhghyWg6AAAAAElFTkSuQmCC
EOF
