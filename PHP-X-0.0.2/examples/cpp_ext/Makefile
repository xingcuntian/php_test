PHP_INCLUDE = `/usr/local/php7/bin/php-config --includes`
PHP_LIBS = `/usr/local/php7/bin/php-config --libs`
PHP_LDFLAGS = `/usr/local/php7/bin/php-config --ldflags`
PHP_INCLUDE_DIR = `/usr/local/php7/bin/php-config --include-dir`
PHP_EXTENSION_DIR = /usr/local/php7/lib/php/extensions/no-debug-non-zts-20160303

cpp_ext.so: extension.cpp
	c++ -DHAVE_CONFIG_H -g -o cpp_ext.so -O0 -fPIC -shared extension.cpp -std=c++11 -lphpx ${PHP_INCLUDE} -I${PHP_INCLUDE_DIR}
test.so: test.cpp
	c++ -DHAVE_CONFIG_H -g -o test.so -O0 -fPIC -shared test.cpp -std=c++11  -lphpx ${PHP_INCLUDE} -I${PHP_INCLUDE_DIR}\
	 -I${PHP_INCLUDE_DIR}/ext/swoole/include -I${PHP_INCLUDE_DIR}/ext/swoole
install: cpp_ext.so
	cp cpp_ext.so ${PHP_EXTENSION_DIR}/
clean:
	rm *.so
