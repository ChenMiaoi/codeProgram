bin = httpserver
cc = g++
LD_FLAG = -std=c++11
src = main.cc
cgi = test_cgi
db  = db_conn
WA_FLAG = -Wl,--no-as-needed
P_LAB = -lpthread
DB_LAB = -I ../mysqldb/include -L ../mysqldb/lib -lmysqlclient
STATIC = -static
output_dir = build
release_dir = release

ALL:$(bin) $(cgi) $(db) build
.PHONY:ALL

$(bin):$(src)
	$(cc) -o $@ $^ $(LD_FLAG) $(WA_FLAG) $(P_LAB)

$(cgi):cgi/test_cgi.cc
	$(cc) -o $@ $^ $(LD_FLAG)

$(db):cgi/db_conn.cc
	$(cc) -o $@ $^ $(LD_FLAG)  $(WA_FLAG) $(P_LAB) $(DB_LAB) $(STATIC)

build:
	mkdir -p $(output_dir)/$(release_dir)
	mv $(bin) $(output_dir)
	mv $(cgi) ../wwwroot
	mv $(db) ../wwwroot

.PHONY:clean
clean:
	rm -rf $(output_dir) ../wwwroot/$(cgi) ../wwwroot/$(db)

.PHONY:run
run:
	./$(output_dir)/$(bin) 8081

.PHONY:release
release:
	cp -r ../wwwroot $(output_dir)/$(release_dir)/wwwroot
	cp -r $(output_dir)/$(bin) $(output_dir)/$(release_dir)

