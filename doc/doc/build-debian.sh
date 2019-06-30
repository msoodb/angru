ssh root@xxx.xxx.xxx.xxx
cat /etc/os-release
adduser angru
usermod -aG sudo angru
su - angru
exit
apt-get install sudo
exit
#--------------------------------------------------------------------------#
# create ssh-key on development machine
ssh-copy-id angru@198.143.183.251
chmod 700 ~/.ssh
chmod 600 ~/.ssh/authorized_keys
ssh angru@198.143.183.251
#--------------------------------------------------------------------------#
sudo apt-get check
sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get clean all
sudo apt-get install nano wget curl net-tools lsof bash-completion
# ls -a if .ssh dose not
# exist mkdir .ssh
cd ~/.ssh
ssh-keygen
cat id_rsa.pub
copy id_rsa.pub to deploy key to angru project on github
#--------------------------------------------------------------------------#
sudo apt-get install build-essential
sudo apt-get install git-all
sudo apt-get install cmake
#--------------------------------------------------------------------------#
sudo apt install postgresql postgresql-contrib
# sudo postgresql-setup initdb
# sudo vi /var/lib/pgsql/data/pg_hba.conf
sudo vi /etc/postgresql/9.6/main/pg_hba.conf

		pg_hba.conf excerpt (original)
local   all             postgres                                peer
host    all             all             127.0.0.1/32            ident
host    all             all             ::1/128                 ident

		pg_hba.conf excerpt (updated)

local   all             postgres                                md5
host    all             all             127.0.0.1/32            md5
host    all             all             ::1/128                 md5

sudo systemctl start postgresql
sudo systemctl enable postgresql
sudo -i -u postgres
#--------------------------------------------------------------------------#
cd ~
git clone git@github.com:msoodb/angru.git
#--------------------------------------------------------------------------#
# sudo apt-get install  https:# download.postgresql.org/pub/repos/apt-get/9.6/redhat/rhel-7-x86_64/pgdg-redhat96-9.6-3.noarch.rpm -y
# sudo apt-get install postgresql96 postgresql96-server postgresql96-contrib postgresql96-libs -y
# sudo /usr/pgsql-9.6/bin/postgresql96-setup initdb
# sudo systemctl enable postgresql-9.6.service
# sudo systemctl start postgresql-9.6.service
#--------------------------------------------------------------------------#
sudo -i -u postgres
psql
create user angru;
alter user angru password '1235';
alter user angru with superuser;
create database angrudb;
# alter database angrudb owner to angru;
grant ALL on DATABASE angrudb to angru;
\q
exit
psql -f angru/database/angrudb.sql angrudb
# pg_restore -d angrudb -c ~/angru/database/angrudb/angrudb.dump
# pg_dump angrudb -c -Ft -f ~/Projects/angru/database/angrudb/angrudb.dump
sudo -i -u postgres
psql
alter user angru with nosuperuser;
#--------------------------------------------------------------------------#
sudo apt update
sudo apt install openssl
sudo apt install libssl-dev
sudo apt install libboost-all-dev
sudo apt install rapidjson-dev
sudo apt install libpqxx-dev
sudo apt install libvmime-dev
git clone git@github.com:oktal/pistache.git
cd pistache/include/pistache/
# vi common.h # change file uplaod size to 1024*1024*1024
vi config.h # static constexpr size_t DefaultMaxPayload = 1024 * 1024 * 1024;
cd ~/pistache
mkdir build
cd build
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
# git clone git@github.com:arun11299/cpp-jwt.git
#--------------------------------------------------------------------------#
sudo apt-get update
sudo apt-get upgrade
sudo lsof -i:80 #  check if apache2 is installed then sudo apt remove apache2
sudo apt-get install nginx
sudo systemctl restart nginx
sudo systemctl start nginx

ps -ef | grep nginx
sudo /usr/local/nginx/sbin/nginx -t # test nginx
/etc/nginx/sites-available$ sudo vi default
	upstream backend {
   		server 127.0.0.1:9080;
   		server 127.0.0.1:9081;
	   	server 127.0.0.1:9082;
	}
	server
	{
		listen 8592;
		server_name ahrv;
		location / {
		proxy_pass "http://backend";
		}
	}
sudo nginx -t
sudo nginx -s reload

/etc/nginx$ sudo vi nginx.conf
http {
    client_max_body_size 1024M;
    # other lines...
}
sudo service nginx restart
#--------------------------------------------------------------------------#
sudo apt install supervisor
sudo touch /etc/supervisor/conf.d/angru_script.conf
sudo vi /etc/supervisor/conf.d/angru_script.conf
	[program:angru_script_1]
	command=/home/angru/angru/build/src/angru 9080
	autostart=true
	autorestart=true
	stderr_logfile=/var/log/angru.err.log
	stdout_logfile=/var/log/angru.out.log

	[program:angru_script_2]
	command=/home/angru/angru/build/src/angru 9081
	autostart=true
	autorestart=true
	stderr_logfile=/var/log/angru.err.log
	stdout_logfile=/var/log/angru.out.log

	[program:angru_script_3]
	command=/home/angru/angru/build/src/angru 9082
	autostart=true
	autorestart=true
	stderr_logfile=/var/log/angru.err.log
	stdout_logfile=/var/log/angru.out.log
sudo supervisorctl reread
sudo supervisorctl update

cd ~/angru
mkdir build
mkdir avatars
mkdir files
cd build
cmake -DCMAKE_BUILD_TYPE=Release ../
make

sudo supervisorctl # restart all instance of angru
# supervisorctl command: status, stop, start, restart All, quit
#--------------------------------------------------------------------------#
HTTPS:
sudo apt-get install certbot python-certbot-nginx #-t stretch-backports
sudo certbot --nginx
#--------------------------------------------------------------------------#
cdn
server
{
	server_name cdn.zeus.cloudns.org;
	root /home/angru/angru/files;
	location / {
		root /home/angru/angru/files;
	}
}
