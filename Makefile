SERV_TARGET=r-type_server
CLIENT_TARGET=r-type_client
DIR=build

all:
	cmake . -B $(DIR) -DCMAKE_TOOLCHAIN_FILE=/home/nellymegaswag/Documents/delivery/B-CPP-500-LYN-5-2-rtype-nathan.baudelin/vcpkg/scripts/buildsystems/vcpkg.cmake
	make -C $(DIR)
	cp $(DIR)/serveur/$(SERV_TARGET) .
	cp $(DIR)/client/$(CLIENT_TARGET) .

clean:
	rm -rf $(DIR)

fclean: clean
	rm -f $(SERV_TARGET)
	rm -f $(CLIENT_TARGET)

re: fclean all

.PHONY: all debug clean fclean re