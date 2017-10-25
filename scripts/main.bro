@load base/frameworks/notice
@load base/protocols/ssl

module ROCA;

export {
	## Set to true to raise a notice for each host/certificate combination
	## that was identified to have a CVE-2017-15361 key.
	const Notify = F &redef;

	redef enum Notice::Type += {
		## Indicates that the server is using a key that is potentially affected
		## by CVE-2017-15361.
		CVE_2017_15361_KEY
	};
}

event x509_certificate(f: fa_file, cert_ref: opaque of x509, cert: X509::Certificate) {
	if ( Notify == F )
		return;

	if ( ! roca_vulnerable_cert(cert_ref) )
		return;

	local idstring = "";

	if ( f?$conns && |f$conns| == 1 )
		for ( id in f$conns )
			{
			idstring = cat(id$orig_h);
			break;
			}

	local note = Notice::Info($note=CVE_2017_15361_KEY,
		$msg="Certificate uses a key potentially affected by CVE-2017-15361",
		$f=f);

	if ( idstring != "" ) {
		note$suppress_for = 1day;
		note$identifier = idstring;
	}

	NOTICE(note);
}
