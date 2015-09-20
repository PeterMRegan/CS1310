#Peter Regan
#19 Sept 2015
#Python Project for CS1310

room_dict = {}
item_dict = {}

class room:
	def __init__(self, name):
		self.name = name
		self.description = ''
		self.exits = {}
		self.items = {}

	def set_exit(self, direction, new_location):
		self.exits.setdefault(direction, new_location)

	def add_item(self, item_name, item_dict):
		self.items.setdefault(item_name, item_dict)

	def set_descr(self, descr):
		self.description = descr

class item:
	def __init__(self, name):
		self.name = name
		self.dict = {}

	def set_values(self, attribute, value):
		self.dict.setdefault(attribute, value)

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

def main():
	initialize_rooms()
	current_room = 'test0'
	game_over = 0
	user_command = 0
	input ('Welcome to Peter\'s silly game! Please use north, south, east, west, up, down to move around. Other commands will become avaliable later! (Press Enter to continue)')
	print ('\n' + room_dict[current_room].name, room_dict[current_room].description)
	while game_over != 1:
		user_command = input (':')
		action = parse_input(user_command)
		if action == 'quiting':
			game_over = 1
		elif action == 'movement':
			direction = movement_normalization(user_command)
			current_room = move(current_room, direction)
		else:
			print ('That was not a recognized command, please try again')

	print ('Goodbye, thanks for playing!')
main()
