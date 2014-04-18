mkdir lastresortrecovery_0.2-beta
cp -r DEBIAN lastresortrecovery_0.2-beta
git clone http://github.com/GUI2BCD/Agent.git
cd Agent/src
make DESTDIR="../../lastresortrecovery_0.2-beta/" install
cd ../..
dpkg-deb --build lastresortrecovery_0.2-beta
rm -rf Agent
rm -rf lastresortrecovery_0.2-beta
