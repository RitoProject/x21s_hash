#barrystyle 05112018
import x21s_hash, os, sys, time, binascii

#result should be:
#block 0000e25882f725cfa68fc8c7ca244ca14df10241cb50a4b2e6c4b01580878ea4
#nonce was 40847

def gennonce(decnonce):
  hexnonce = str(hex(decnonce)).replace('0x','')
  while len(hexnonce) < 8:
    hexnonce = '0' + hexnonce
  return str(hexnonce)

#main
header = '00112233'
while len(header) < 152:
  header = '00' + header

target = "0000ffff00000000000000000000000000000000000000000000000000000000"
targetbin = binascii.unhexlify(target)
nonce = 0
while True:
  
  complete_header = str(header) + str(gennonce(nonce))
  hashbin = x21s_hash.getPoWHash(binascii.unhexlify(complete_header))[::-1]

  if hashbin < targetbin:
     print 'block ' + str(binascii.hexlify(hashbin))
     print 'nonce was ' + str(nonce)
     sys.exit(0)

  if (nonce % 128 == 0):
     fnonce = str(hex(nonce)).replace('0x','')
     while len(fnonce) < 8:
      fnonce = '0' + fnonce
     print fnonce

  nonce += 1

