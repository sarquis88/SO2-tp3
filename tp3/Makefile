FLAGS_GCC = -std=gnu11 -Wall -Werror -pedantic -Wextra -Wconversion -lulfius -ljansson
FLAGS_CPP = --enable=performance,portability,information,unusedFunction -q

make:
	cppcheck $(FLAGS_CPP) ./
	gcc $(FLAGS_GCC) src/status.c src/server_utils.c src/hard_info.c -o bin/status
	gcc $(FLAGS_GCC) src/users.c src/server_utils.c src/users_info.c -o bin/users
	@printf "\nCompilación terminada\n"
	@printf "\nANTE CUALQUIER DUDA, RTF README\n\n"
clean:
	rm bin/*
	rm -r html/ latex/
install:
	useradd sistemas-operativos
	cp ./bin/status /usr/bin/server_status && cp ./bin/users /usr/bin/server_users
	cp ./install_files/*.service /lib/systemd/system/ &&	cp ./install_files/*.service /etc/systemd/system/
	touch /var/log/users.log && touch /var/log/status.log
	chown sistemas-operativos /var/log/users.log && chown sistemas-operativos /var/log/status.log
	chown sistemas-operativos /usr/bin/server_users &&	chown sistemas-operativos /usr/bin/server_status
	systemctl daemon-reload
	cp ./install_files/so2-tp3.conf /etc/nginx/sites-available/
	ln -s /etc/nginx/sites-available/so2-tp3.conf /etc/nginx/sites-enabled/so2-tp3
	cp ./install_files/so2-tp3.passwd /etc/nginx/.so2-tp3.passwd
	nginx -s reload
	make start
	@printf "\nInstalación terminada\n"
	@printf "\nSE DEBE AGREGAR 'sistemas-operativos ALL = NOPASSWD:/usr/sbin/useradd' a /etc/sudoers\n\n"
uninstall:
	make stop
	rm /usr/bin/server_users && rm /usr/bin/server_status
	rm /lib/systemd/system/server_users.service && rm /lib/systemd/system/server_status.service
	rm /etc/systemd/system/server_users.service && rm /etc/systemd/system/server_status.service
	rm /var/log/users.log && rm /var/log/status.log
	rm /etc/nginx/sites-enabled/so2-tp3 && rm /etc/nginx/sites-available/so2-tp3.conf
	rm /etc/nginx/.so2-tp3.passwd
	systemctl daemon-reload
	nginx -s reload
	userdel sistemas-operativos
	@printf "\nDesinstalación terminada\n\n"
reinstall:
	make uninstall &&	make install
	@printf "\nReinstalación terminada\n\n"
enable:
	systemctl enable server_status && systemctl enable server_users
disable:
	systemctl disable server_status && systemctl disable server_users
start:
	systemctl start server_status && systemctl start server_users
stop:
	systemctl stop server_status &&	systemctl stop server_users
restart:
	systemctl restart server_status &&	systemctl restart server_users
reload:
	systemctl reload server_status &&	systemctl reload server_users
check:
	service server_status status && service server_users status
docs:
	doxygen Doxyfile
