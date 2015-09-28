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

	def set_exit(self, direction, new_location):
		self.exits.setdefault(direction, new_location)

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
			item_dict.setdefault(current_item, item(temp_list[1]))
		elif temp_list[0] == 'Keyword':
			a = 1
			while a < len(temp_list):
				item_dict[current_item].add_keyword(temp_list[a])
				a += 1
		elif temp_list[0] == 'Description1':
			item_dict[current_item].set_value('primary description', temp_list[1].strip('\n'))
		elif temp_list[0] == 'Description2':
			item_dict[current_item].set_value('visual description', temp_list[1].strip('\n'))
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
			room_dict.setdefault(current_room, room(temp_list[1]))
		elif temp_list[0] == 'Description':
			room_dict[current_room].set_descr(temp_list[1].strip('\n'))
		elif temp_list[0] == 'Exit':
			room_dict[current_room].set_exit(temp_list[1],temp_list[2].rstrip('\n'))

def move(current_location, direction):
	room_dict[current_location].set_exit(direction, 0)
	if room_dict[current_location].exits[direction] == 0:
		print ('You cannot go in that direction')
		return current_location
	else:
		new_room = room_dict[current_location].exits[direction]
		print ('\n' + room_dict[new_room].name, room_dict[new_room].description)
		return new_room

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

def display_items(room):
	if len(room_dict[room].items) == 0:
	 return 'no items'
	else:
		for item in range(0,len(room_dict[room].items)):
			print (item_dict[room_dict[room].items[item]].dict['primary description'])

def get_item(room, user_command):
	a = 0
	temp = 2
	temp_list = user_command.split()
	if len(temp_list) == 1:
		print ('Get what?')
	else:
		item = temp_list[1]
		while temp < len(temp_list):
			item = item + temp_list[temp]
		found = False
		while a < len(room_dict[room].items) and found == False:
			b = 0
			while found == False and b < len(item_dict[room_dict[room].items[a]].keywords):
				if item == item_dict[room_dict[room].items[a]].keywords[b]:
					if len(player_inventory) < MAX_ITEMS:
						player_inventory.append(room_dict[room].items[a])
						print ('You get the', room_dict[room].items[a])
						found == True
					else:
						print ('You can\'t carry that many items')
				else:
					b += 1
			a += 1
		if found == False:
			print ('That item is not here.')
		else:
			room_dict[room].rem_item(room_dict[room].items[a])

def main():
	initialize_rooms()
	initialize_items()
	current_room = 'test0'
	game_over = 0
	user_command = 0
	input ('Welcome to Peter\'s silly game! Please use north, south, east, west, up, down to move around. Other commands will become avaliable later! (Press Enter to continue)')
	print ('\n', room_dict[current_room].name, room_dict[current_room].description)
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
		else:
			print ('That was not a recognized command, please try again')

	print ('Goodbye, thanks for playing!')
main()
