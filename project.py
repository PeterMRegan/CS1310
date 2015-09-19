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
	room_dict = {}
	room_file = open('rooms.txt', 'r')
	for line in room_file:
		temp_list = line.split(':')
		if temp_list[0] == 'Name':
			current_room = temp_list[1].rstrip('\n')
			room_dict.setdefault(current_room, room(temp_list[1]))
		elif temp_list[0] == 'Description':
			room_dict[current_room].set_descr(temp_list[1].rstrip('\n'))
		elif temp_list[0] == 'Exit':
			room_dict[current_room].set_exit(temp_list[1],temp_list[2].rstrip('\n'))
	return room_dict
			

def main():
	room_dict = initialize_rooms()
	print (room_dict['test'].exits)

main()
