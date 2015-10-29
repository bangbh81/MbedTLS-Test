#ifndef __MBEDTLS_CONFIGURATION
#define __MBEDTLS_CONFIGURATION

/*configuration order
0.Have to increase Stack Size


1. Var define
	mbedtls_entropy_context _entropy;
    mbedtls_ctr_drbg_context _ctr_drbg;
    mbedtls_x509_crt _cacert;
    mbedtls_ssl_context _ssl;
    mbedtls_ssl_config _ssl_conf;

2. Var init
	mbedtls_entropy_init(&_entropy);
	mbedtls_ctr_drbg_init(&_ctr_drbg);
	mbedtls_x509_crt_init(&_cacert);
	mbedtls_ssl_init(&_ssl);
	mbedtls_ssl_config_init(&_ssl_conf);

3. Init TLS-related stuf

	mbedtls_ctr_drbg_seed();
	mbedtls_x509_crt_parse(&_cacert, (const unsigned char *) SSL_CA_PEM,
                           sizeof (SSL_CA_PEM))

	mbedtls_ctr_drbg_seed(&_ctr_drbg, mbedtls_entropy_func, &_entropy,
                          (const unsigned char *) DRBG_PERS,
                          sizeof (DRBG_PERS))

 	mbedtls_ssl_config_defaults(&_ssl_conf,
                        MBEDTLS_SSL_IS_CLIENT,
                        MBEDTLS_SSL_TRANSPORT_STREAM,
                        MBEDTLS_SSL_PRESET_DEFAULT)

	mbedtls_ssl_conf_ca_chain(&_ssl_conf, &_cacert, NULL);
	mbedtls_ssl_conf_rng(&_ssl_conf, mbedtls_ctr_drbg_random, &_ctr_drbg);

#if authmode
	mbedtls_ssl_conf_authmode(&_ssl_conf, MBEDTLS_SSL_VERIFY_OPTIONAL);
#endif

#if debug
	mbedtls_ssl_conf_verify(&_ssl_conf, my_verify, NULL);
	mbedtls_ssl_conf_dbg(&_ssl_conf, my_debug, NULL);
	mbedtls_debug_set_threshold(DEBUG_LEVEL);
#endif

	mbedtls_ssl_setup(&_ssl, &_ssl_conf)

	mbedtls_ssl_set_hostname(&_ssl, HTTPS_SERVER_NAME);

	mbedtls_ssl_set_bio(&_ssl, static_cast<void *>(&_stream),
                                   ssl_send, ssl_recv, NULL );

end. free init
	mbedtls_entropy_free(&_entropy);
	mbedtls_ctr_drbg_free(&_ctr_drbg);
	mbedtls_x509_crt_free(&_cacert);
	mbedtls_ssl_free(&_ssl);
	mbedtls_ssl_config_free(&_ssl_conf);
*/
#endif
