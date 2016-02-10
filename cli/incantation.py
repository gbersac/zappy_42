from resource import Inventory, Resource
# from trantor import Trantor

class Incantation:

	def __init__(self, nb_player, prerequisites):
		self.nb_player = nb_player
		self.prerequisites = prerequisites

	def is_trantor_ready(trantor):
		""" Test if the trantor has all the resources needed for this """
		""" incantation """
		level = trantor.level
		incant = Incantation.incant_list[level]
		for res in Resource:
			if incant.prerequisites.get_qt(res) > trantor.inventory.get_qt(res):
				return False
		return True

	def missing_resources(trantor):
		level = trantor.level
		incant = Incantation.incant_list[level]
		to_return = []
		for res in Resource:
			if incant.prerequisites.get_qt(res) > trantor.inventory.get_qt(res):
				to_return.append(res)
		return to_return

Incantation.incant_list = {
	1 : Incantation(1, Inventory.from_nbrs(0, 1, 0, 0, 0, 0, 0)),
	2 : Incantation(2, Inventory.from_nbrs(0, 1, 1, 1, 0, 0, 0)),
	3 : Incantation(2, Inventory.from_nbrs(0, 2, 0, 1, 0, 2, 0)),
	4 : Incantation(4, Inventory.from_nbrs(0, 1, 1, 2, 0, 1, 0)),
	5 : Incantation(4, Inventory.from_nbrs(0, 1, 2, 1, 3, 0, 0)),
	6 : Incantation(6, Inventory.from_nbrs(0, 1, 2, 3, 0, 1, 0)),
	7 : Incantation(6, Inventory.from_nbrs(0, 2, 2, 2, 2, 2, 1))
}
