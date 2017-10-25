# @TEST-EXEC: bro -C -r $TRACES/vulnerable.pcap %INPUT
# @TEST-EXEC: bro -C -r $TRACES/not-vulnerable.pcap %INPUT
# @TEST-EXEC: btest-diff .stdout

event x509_certificate(f: fa_file, cert_ref: opaque of x509, cert: X509::Certificate) {
	print roca_vulnerable_cert(cert_ref);
}
