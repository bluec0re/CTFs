#!/usr/bin/env python
# encoding: utf-8


a = r'[[c%l][c{g}[%{%Mc%spdgj=]T%aat%=O%bRu%sc]c%ti[o%n=Wcs%=No[t=T][hct%=buga[d=As%=W]e=T%ho[u%[%g]h%t[%}%'
#a = r'[[c%l][c{g}[%{%Mc%spdggfdj=]T%aat%=O%bRu%sc]c%ti[o[t=T][hct%=budsga[d=As%=W]e=T%ho[u%[%g]h%t[%}%T[]e3'

a = a.replace('spdgj', 'yb%e')
print(a)
a = a.replace('aat', 'his')
print(a)
a = a.replace('buga', 'Goo')
print(a)
a = a.replace('=', ' ')
print(a)
a = a.replace('}', '', 1)
print(a)
a = a.replace('{', '', 1)
print(a)
a = a.replace('R', 'f', 1)
print(a)
a = a.replace('c', 'f', 1)
print(a)
a = a.replace(']', '')
print(a)
a = a.replace('[', '')
print(a)
a = a.replace('%', '')
print(a)
a = a.replace('c', 'a')
print(a)
a = a.replace('aa', 'ca')
print(a)

#flag{Maybe This Obfuscation Was Not That Good As We Thought}
