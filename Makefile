SERV_TARGET=r-type_server
CLIENT_TARGET=r-type_client
DIR=build

all:
	cmake . -B $(DIR)
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