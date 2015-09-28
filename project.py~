#Peter Regan
#19 Sept 2015
#Python Project for CS1310

room_dict = {}
item_dict = {}
player_inventory = []
MAX_ITEMS = 4

class room:
	def __init__(self, name):
		self.name = name
		self.description = ''
		self.exits = {}
		self.items = []
		self.display_name = 'Default'

	def set_display_name(self, name):
		self.display_name = name

	def set_exit(self, direction, exit_attributes):
		self.exits.setdefault(direction, exit_attributes)

	def add_item(self, item_name):
		self.items.append(item_name)

	def rem_item(self, item_name):
		self.items.remove(item_name)

	def set_descr(self, descr):
		self.description = descr

class item:
	def __init__(self, name):
		self.name = name
		self.dict = {}
		self.keywords = []
		self.display_name = 'Default'

	def set_display_name(self, name):
		self.display_name = name

	def set_value(self, attribute, value):
		self.dict.setdefault(attribute, value)

	def add_keyword(self, keyword):
		self.keywords.append(keyword)

def initialize_items():
	temp_list = []
	list_file = open('items.txt', 'r')
	current_item = 0
	for line in list_file:
		temp_list = line.split(':')
		if temp_list[0] == 'Name':
			current_item = temp_list[1].strip('\n')
			item_dict.setdefault(current_item, item(temp_list[1].strip('\n')))
			item_dict[current_item].set_display_name(temp_list[2].strip('\n'))
		elif temp_list[0] == 'Keyword':
			a = 1
			while a < len(temp_list):
				item_dict[current_item].add_keyword(temp_list[a].strip('\n'))
				a += 1
		elif temp_list[0] == 'Description2':
			item_dict[current_item].set_value('primary description', temp_list[1].strip('\n'))
		elif temp_list[0] == 'Description1':
			item_dict[current_item].set_value('visual description', temp_list[1].strip('\n'))
		elif temp_list[0] == 'Usage':
			item_dict[current_item].set_value('usage', temp_list[1].strip('\n'))
		elif temp_list[0] == 'Value':
			item_dict[current_item].set_value('value', int(temp_list[1].strip('\n')))
		elif temp_list[0] == 'Location':
			item_location = temp_list[1].strip('\n')
			room_dict[item_location].add_item(current_item)

def initialize_rooms():
	temp_list = []
	current_room = 0
	room_file = open('rooms.txt', 'r')
	for line in room_file:
		temp_list = line.split(':')
		if temp_list[0] == 'Name':
			current_room = temp_list[1].strip('\n')
			room_dict.setdefault(current_room, room(temp_list[1].strip('\n')))
			room_dict[current_room].set_display_name(temp_list[2].strip('\n'))
		elif temp_list[0] == 'Description':
			room_dict[current_room].set_descr(temp_list[1].strip('\n'))
		elif temp_list[0] == 'Exit':
			room_exit = []
			for attribute in temp_list:
				room_exit.append(attribute.strip('\n'))
			room_dict[current_room].set_exit(temp_list[1],room_exit)

def display_room(room):
	print ('\n' + room_dict[room].display_name + '\n' + room_dict[room].description)

def move(current_location, direction):
	room_dict[current_location].set_exit(direction, 0)
	if room_dict[current_location].exits[direction] == 0:
		print ('You cannot go in that direction')
		return current_location
	else:
		if room_dict[current_location].exits[direction][3] == 'unblocked':
			new_room = room_dict[current_location].exits[direction][2]
			display_room(new_room)
			display_items(new_room)
			return new_room
		elif room_dict[current_location].exits[direction][5] == 'possesses' and has_item(room_dict[current_location].exits[direction][4]) == True:
			new_room = room_dict[current_location].exits[direction][2]
			print (room_dict[current_location].exits[direction][7])
			display_room(new_room)
			display_items(new_room)
			return new_room
		else:
			print (room_dict[current_location].exits[direction][6])
			return current_location

def has_item(item):
	found = False
	a = 0
	while a < len(player_inventory) and found == False:
		if player_inventory[a] == item:
			found = True
		else:
			a += 1
	return found

def movement_normalization(direction):
	if direction == 'n':
		direction = 'north'
	elif direction == 'e':
		direction = 'up'
	elif direction == 's':
		direction = 'south'
	elif direction == 'w':
		direction = 'west'
	elif direction == 'u':
		direction = 'up'
	elif direction == 'd':
		direction = 'down'
	elif direction == 'north' or direction == 'east' or direction == 'south' or direction == 'west' or direction == 'up' or direction == 'down':
		direction = direction
	else:
		direction = 0
	return direction

def parse_input(user_input):
	temp_list = user_input.split(' ')
	if temp_list[0] == 'n' or temp_list[0] == 'w' or temp_list[0] == 's' or temp_list[0] == 'e' or temp_list[0] == 'u' or temp_list[0] == 'd' or temp_list[0] == 'enter' or temp_list[0] == 'north' or temp_list[0] == 'east' or temp_list[0] == 'south' or temp_list[0] == 'west' or temp_list[0] == 'up' or temp_list[0] == 'down':
		return 'movement'
	elif temp_list[0] == 'get' or (temp_list[0] == 'pick' and temp_list[1] == 'up'):
		return 'get item'
	elif temp_list[0] == 'drop':
		return 'drop item'
	elif temp_list[0] == 'q' or temp_list[0] == 'quit':
		return 'quiting'
	elif temp_list[0] == 'i' or temp_list[0] == 'inventory':
		return 'inventory'
	elif temp_list[0] == 'l' or temp_list[0] == 'look':
		return 'look'
	else:
		a = 0
		found = False
		while a < len(player_inventory) and found == False:
			item_dict[player_inventory[a]].set_value('usage', 'fail_safe_parameter')
			if temp_list[0] == item_dict[player_inventory[a]].dict['usage']:
				found = True
				return 'usage'
			else:
				a += 1
		if found == False:
			return 'unknown'

def look(room, user_command):
	a = 0
	command_length = 2
	command_list = user_command.split()
	if len(command_list) == 1:
		display_room(room)
		display_items(room)
	else:
		item = command_list[1]
		while command_length < len(command_list):
			item = item + " " + command_list[command_length]
			command_length += 1
		found = False
		while a < len(player_inventory) and found == False:
			b = 0
			while b < len(item_dict[player_inventory[a]].keywords) and found == False:
				if item == item_dict[player_inventory[a]].keywords[b]:
					print (item_dict[player_inventory[a]].dict['visual description'])
					found = True
				else:
					b += 1
			a += 1
		a = 0
		while a < len(room_dict[room].items) and found == False:
			b = 0
			while found == False and b < len(item_dict[room_dict[room].items[a]].keywords):
				if item == item_dict[room_dict[room].items[a]].keywords[b]:
					print (item_dict[room_dict[room].items[a]].dict['visual description'])
					found = True
				else:
					b += 1
			a += 1

def inventory():
	print ('You have:')
	if len(player_inventory) == 0:
		print ('Nothing!')
	else:
		for item in player_inventory:
			print (item_dict[item].display_name)

def display_items(room):
	if len(room_dict[room].items) == 0:
	 return 'no items'
	else:
		for item in range(0,len(room_dict[room].items)):
			print (item_dict[room_dict[room].items[item]].dict['primary description'])

def drop_item(room, user_command):
	a = 0
	command_length = 2
	command_list = user_command.split()
	if len(command_list) == 1:
		print ('Drop what?')
	else:
		item = command_list[1]
		while command_length < len(command_list):
			item = item + " " + command_list[command_length]
			command_length += 1
		found = False
		dropped = False
		while a < len(player_inventory) and found == False:
			b = 0
			while b < len(item_dict[player_inventory[a]].keywords) and found == False:
				if item == item_dict[player_inventory[a]].keywords[b]:
					if len(room_dict[room].items) < MAX_ITEMS:
						room_dict[room].add_item(player_inventory[a])
						print ('You drop the', item_dict[player_inventory[a]].display_name)
						found = True
						dropped = True
					else:
						print ('There\'s not enough room for that here')
						found = True
				else:
					b += 1
			if found == False:
				a += 1
		if found == False:
			print ('You don\'t have that item')
		elif found == True and dropped == True:
			player_inventory.remove(player_inventory[a])

def get_item(room, user_command):
	a = 0
	command_length = 2
	command_list = user_command.split()
	if len(command_list) == 1:
		print ('Get what?')
	else:
		item = command_list[1]
		while command_length < len(command_list):
			item = item + " " + command_list[command_length]
			command_length += 1
		found = False
		aquired = False
		while a < len(room_dict[room].items) and found == False:
			b = 0
			while found == False and b < len(item_dict[room_dict[room].items[a]].keywords):
				if item == item_dict[room_dict[room].items[a]].keywords[b]:
					if len(player_inventory) < MAX_ITEMS:
						player_inventory.append(room_dict[room].items[a])
						print ('You get the', item_dict[room_dict[room].items[a]].display_name)
						found = True
						aquired = True
					else:
						print ('You can\'t carry that many items')
						found = True
				else:
					b += 1
			if found == False:
				a += 1
		if found == False:
			print ('That item is not here.')
		elif found == True and aquired == True:
			room_dict[room].rem_item(room_dict[room].items[a])

def use_item(user_command, room):
	command_list = user_command.split()
	found = False
	a = 0
	command_length = 2
	command_list = user_command.split()
	if len(command_list) == 1:
		print ('With what?')
	else:
		item = command_list[1]
		while command_length < len(command_list):
			item = item + " " + command_list[command_length]
			command_length += 1
		for exit in room_dict[room].exits:
			if len(room_dict[room].exits[exit]) > 4:
				required_item = room_dict[room].exits[exit][4]
				if room_dict[room].exits[exit][5] == 'usage' and has_item(required_item) == True:
					while a < len(item_dict[required_item].keywords) and found == False:
						if item == item_dict[required_item].keywords[a]:
							print (room_dict[room].exits[exit][7])
							room_dict[room].exits[exit][3] = 'unblocked'
							found = True
							player_inventory.remove(required_item)
						else:
							a += 1
		if found == False:
			print ('You cannot do that here')

def main():
	initialize_rooms()
	initialize_items()
	current_room = 'test0'
	game_over = 0
	user_command = 0
	input ('Welcome to Peter\'s silly game! Please use north, south, east, west, up, down to move around. Other commands will become avaliable later! (Press Enter to continue)')
	display_room(current_room)
	display_items(current_room)
	while game_over != 1:
		user_command = input (':')
		action = parse_input(user_command)
		if action == 'quiting':
			game_over = 1
		elif action == 'movement':
			direction = movement_normalization(user_command)
			current_room = move(current_room, direction)
		elif action == 'get item':
			get_item(current_room, user_command)
		elif action == 'drop item':
			drop_item(current_room, user_command)
		elif action == 'inventory':
			inventory()
		elif action == 'look':
			look(current_room, user_command)
		elif action == 'usage':
			use_item(user_command, current_room)
		else:
			print ('That was not a recognized command, please try again')

	print ('Goodbye, thanks for playing!')

main()
