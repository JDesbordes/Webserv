rm -rf ./server/htdocs/save
rm -rf ./server/htdocs/YoupiBanane

mkdir ./server/htdocs/save

mkdir ./server/htdocs/YoupiBanane
touch ./server/htdocs/YoupiBanane/youpi.bad_extension
touch ./server/htdocs/YoupiBanane/youpi.bla

mkdir ./server/htdocs/YoupiBanane/nop
touch ./server/htdocs/YoupiBanane/nop/youpi.bad_extension
touch ./server/htdocs/YoupiBanane/nop/other.pouic

mkdir ./server/htdocs/YoupiBanane/Yeah
touch ./server/htdocs/YoupiBanane/Yeah/not_happy.bad_extension

echo "[youpi.bad_extension] (nop)" > ./server/htdocs/YoupiBanane/nop/youpi.bad_extension
echo "[youpi.bad_extension (directory)]" > ./server/htdocs/YoupiBanane/youpi.bad_extension
echo "[not_happy.bad_extension (Yeah)]" > ./server/htdocs/YoupiBanane/Yeah/not_happy.bad_extension

./testers/ubuntu_tester http://localhost:8001
