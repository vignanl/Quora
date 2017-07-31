class Tree(object):
	"""docstring for Tree."""
	def __init__(self,n,nodes):
		self.no_of_nodes = n
		self.root = None
		self.nodes = nodes
		self.adjacency_list = {}
		self.optimum_root = None
		self.visit = []

	def set_root(self):
	 	branches = [[x[0],len(x[1])] for x in self.adjacency_list.items()]
	#	print "branches ", branches
		max_root = max(branches, key = lambda x : x[1])
	#	print max_root
		self.root = max_root[0]


	def add_edge(self,x,y):
		if x in self.adjacency_list:
			self.adjacency_list[x].append(y)
		else:
			self.adjacency_list[x] = [y]

		if y in self.adjacency_list:
			self.adjacency_list[y].append(x)
		else:
			self.adjacency_list[y] = [x]

	def dfs(self,node_p,root_branch_no,sum_parent):
		adj_list = self.adjacency_list[node_p]
		count = 0
		print "node ", node_p, " childs ", adj_list
		self.nodes[node_p].parent_path_sum = sum_parent
		self.nodes[node_p].parent_branch_index = root_branch_no
		#print "node ", node_p, " childs ", adj_list
		for ch in adj_list:
			if self.visit[ch] == 0:
				count = count + 1
				self.visit[ch] = 1
				sum_branch = self.dfs(ch,root_branch_no,sum_parent+self.nodes[node_p].cost)
				self.nodes[node_p].children_path_sum.append(sum_branch)
		count = max(1,count)
		return count*self.nodes[node_p].cost + sum(self.nodes[node_p].children_path_sum)

	def traversal(self):
		self.visit = [0 for i in range(self.no_of_nodes)]
		adj_list = self.adjacency_list[self.root]
		#print adj_list
		branch_count = 0
		self.visit[self.root] = 1
		for ch in adj_list:
			if self.visit[ch] == 0:
				branch_count += 1
				self.visit[ch] = 1
				sum_branch = self.dfs(ch,branch_count,self.nodes[self.root].cost)
				self.nodes[self.root].children_path_sum.append(sum_branch)
		return

	def print_graph(self):
		print "root index ", self.root
		print "root branch sums ", self.nodes[self.root].children_path_sum
		print "Node info"
		for i in range(1,self.no_of_nodes):
			print "node no ", self.nodes[i].ind," parent_br ", self.nodes[i].parent_branch_index, " path_sum ", self.nodes[i].parent_path_sum

	 	return

class Node(object):
	"""docstring for Node."""
	def __init__(self,q_id,weight):
		self.ind = q_id
		self.cost = weight
		self.children_path_sum = []
		self.parent_path_sum = 0
		self.parent_branch_index = -1

def main():
	n = int(raw_input())
	cost = map(int,raw_input().split())
	questions = []
	questions.append(Node(0,0))
	for i in range(1,n+1):
		node_m = Node(i,cost[i-1])
		questions.append(node_m)

	#for i in range(len(questions)):
	#	print questions[i].ind

	#Construct graph
	graph_of_question = Tree(n+1,questions)

	# add edges
	for i in range(n-1):
		edge = map(int,raw_input().split())
		graph_of_question.add_edge(edge[0],edge[1])

	# set default root
	graph_of_question.set_root()
	#print graph_of_question.root
	graph_of_question.traversal()
	graph_of_question.print_graph()
	#build cost matrix
	#find optimum root
	#root = graph_of_question.find_optimum_root()

	#print root+1

if __name__ == "__main__":
	main()
