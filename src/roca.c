// See the file "COPYING" in the main distribution directory for copyright.
//
// This file reimplements the algorithm from https://github.com/crocs-muni/roca

#include <gmp.h>

#define NUMPRIMES 38
static int primes[NUMPRIMES] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101,
103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167};
static mpz_t bnprimes[NUMPRIMES];
static mpz_t markers[NUMPRIMES];

static mpz_t mzero;
static mpz_t rem;
static mpz_t a;
static mpz_t res;
static mpz_t final_res;
static mpz_t bmodulus;

static void initmarkers() {
	mpz_init_set_str(markers[0], "6", 10);
	mpz_init_set_str(markers[1], "30", 10);
	mpz_init_set_str(markers[2], "126", 10);
	mpz_init_set_str(markers[3], "1026", 10);
	mpz_init_set_str(markers[4], "5658", 10);
	mpz_init_set_str(markers[5], "107286", 10);
	mpz_init_set_str(markers[6], "199410", 10);
	mpz_init_set_str(markers[7], "8388606", 10);
	mpz_init_set_str(markers[8], "536870910", 10);
	mpz_init_set_str(markers[9], "2147483646", 10);
	mpz_init_set_str(markers[10], "67109890", 10);
	mpz_init_set_str(markers[11], "2199023255550", 10);
	mpz_init_set_str(markers[12], "8796093022206", 10);
	mpz_init_set_str(markers[13], "140737488355326", 10);
	mpz_init_set_str(markers[14], "5310023542746834", 10);
	mpz_init_set_str(markers[15], "576460752303423486", 10);
	mpz_init_set_str(markers[16], "1455791217086302986", 10);
	mpz_init_set_str(markers[17], "147573952589676412926", 10);
	mpz_init_set_str(markers[18], "20052041432995567486", 10);
	mpz_init_set_str(markers[19], "6041388139249378920330", 10);
	mpz_init_set_str(markers[20], "207530445072488465666", 10);
	mpz_init_set_str(markers[21], "9671406556917033397649406", 10);
	mpz_init_set_str(markers[22], "618970019642690137449562110", 10);
	mpz_init_set_str(markers[23], "79228162521181866724264247298", 10);
	mpz_init_set_str(markers[24], "2535301200456458802993406410750", 10);
	mpz_init_set_str(markers[25], "1760368345969468176824550810518", 10);
	mpz_init_set_str(markers[26], "50079290986288516948354744811034", 10);
	mpz_init_set_str(markers[27], "473022961816146413042658758988474", 10);
	mpz_init_set_str(markers[28], "10384593717069655257060992658440190", 10);
	mpz_init_set_str(markers[29], "144390480366845522447407333004847678774", 10);
	mpz_init_set_str(markers[30], "2722258935367507707706996859454145691646", 10);
	mpz_init_set_str(markers[31], "174224571863520493293247799005065324265470", 10);
	mpz_init_set_str(markers[32], "696898287454081973172991196020261297061886", 10);
	mpz_init_set_str(markers[33], "713623846352979940529142984724747568191373310", 10);
	mpz_init_set_str(markers[34], "1800793591454480341970779146165214289059119882", 10);
	mpz_init_set_str(markers[35], "126304807362733370595828809000324029340048915994", 10);
	mpz_init_set_str(markers[36], "11692013098647223345629478661730264157247460343806", 10);
	mpz_init_set_str(markers[37], "187072209578355573530071658587684226515959365500926", 10);
}

void init_roca() {
	for ( int i = 0; i < NUMPRIMES; ++i )
		mpz_init_set_si(bnprimes[i], primes[i]);

	initmarkers();

	mpz_init(rem);
	mpz_init(a);
	mpz_init(res);
	mpz_init(final_res);
	mpz_init(bmodulus);
}

int vulnerableKey(mpz_t pmod) {
	for ( int i = 0; i < NUMPRIMES; ++i ) {
		mpz_mod(rem, pmod, bnprimes[i]);
		unsigned long int remi = mpz_get_ui(rem);
		mpz_set_si(a, 1);
		mpz_mul_2exp(res, a, remi);
		mpz_and(final_res, res, markers[i]);
		if ( mpz_cmp(final_res, mzero) == 0 ) {
			return 0;
		}
	}

	return 1;
}

int vulnerableKey_hex(const char* hexmod) {
	if ( mpz_set_str(bmodulus, hexmod, 16) != 0 ) {
		return -2;
	}

	return vulnerableKey(bmodulus);
}
