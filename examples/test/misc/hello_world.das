var ctor_count = 0
var to_upper_count = 0
var utf8_count = 0

class MyString
	def MyString
		ctor_count ++
	def to_upper(): MyString?
		to_upper_count ++
		return addr(self)
	def utf8(): MyString?
		utf8_count ++
		return addr(self)

[export]
def main
	let res = new MyString()->to_upper()->utf8()
	print("ctor_count: {ctor_count}\n")
	print("to_upper_count: {to_upper_count}\n")
	print("utf8_count: {utf8_count}\n")


