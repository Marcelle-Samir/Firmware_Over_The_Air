import chilkat

# Create some Chilkat objects and print the versions

zip = chilkat.CkZip()
print("Zip: " + zip.version())

imap = chilkat.CkImap()
print("IMAP: " + imap.version())

ftp = chilkat.CkFtp2()
print("FTP: " + ftp.version())

mailman = chilkat.CkMailMan()
print("POP3/SMTP: " + mailman.version())

ssh = chilkat.CkSsh()
print("SSH: " + ssh.version())

sftp = chilkat.CkSFtp()
print("SFTP: " + sftp.version())

rsa = chilkat.CkRsa()
print("RSA: " + rsa.version())

http = chilkat.CkHttp()
print("RSA: " + http.version())

crypt = chilkat.CkCrypt2()
print("Crypt: " + crypt.version())

xml = chilkat.CkXml()
print("XML: " + xml.version())

sock = chilkat.CkSocket()
print("Socket/SSL/TLS: " + sock.version())

tar = chilkat.CkTar()
print("TAR: " + tar.version())
