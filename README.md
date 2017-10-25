
Johanna::ROCA
=============

This plugin implements detection of CVE-2017-15361 keys; it is a
reimplementation of the source available at
https://github.com/crocs-muni/roca.

This plugin provides two new BIFs that can check public keys:

* `roca_vulnerable_cert` checks if a certificate is vulnerable
* `roca_vulnerable_mod` checks if a modulus is vulerable.

This plugin also ships with a script that is automatically loaded
and can notify you when CVE-2017-15361 are encountered on the wire.

To enable this, set:

```
redef ROCA::Notify=T;
```

Afterwards you should get notice.log entries when such keys are encountered.
Example:

```
#separator \x09
#set_separator	,
#empty_field	(empty)
#unset_field	-
#path	notice
#open	2017-10-25-00-59-28
#fields	ts	uid	id.orig_h	id.orig_p	id.resp_h	id.resp_p	fuid	file_mime_type	file_desc	proto	note	msg	sub	src	dst	p	n	peer_descr	actions	suppress_for	dropped	remote_location.country_code	remote_location.region	remote_location.city	remote_location.latitude	remote_location.longitude
#types	time	string	addr	port	addr	port	string	string	string	enum	enum	string	string	addr	addr	port	count	string	set[enum]	interval	bool	string	string	string	double	double
1449265638.475275	CHhAvVGS1DHFjwGM9	192.168.6.74	52122	104.236.167.107	4433	Fvv5qY2DMGQY2MYQ03	application/x-x509-user-cert	104.236.167.107:4433/tcp	tcp	ROCA::CVE_2017_15361_KEY	Certificate uses a key potentially affected by CVE-2017-15361	-	192.168.6.74	104.236.167.107	4433	-	bro	Notice::ACTION_LOG	86400.000000	F	-	-	-	-	-
#close	2017-10-25-00-59-28
```

Installation
------------

This plugin requires GMP (The GNU MP Bugnum Library) to be installed on the
system. If this is the case, you should be able to install it using bro-pkg
using:

```
bro-pkg install 0xxon/bro-plugin-roca
```

If you have to specify the path to gmp, you can manually clone the repository
and install it using:

```
./configure --with-gmp=[directory]
make install
```
