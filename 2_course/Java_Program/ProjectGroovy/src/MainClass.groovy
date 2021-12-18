//FirstClass first1 = new FirstClass(number: 12,name: "ABC")
//println first1.number + ' ' + first1.name

FirstClass first2 = new FirstClass(2, "2")
println first2.number + ' ' + first2.name

Binding binding = new Binding();
binding.setVariable("number", 91)
binding.setVariable("name", "QueA")
FirstClass first3 = new FirstClass(binding.getVariable("number") as int, binding.getVariable("name") as String)
println first3.getNumber() + ' ' + first3.getName()
println()

String string = "string"
println string instanceof Integer
println()

def first4 = new FirstClass(65, "das auto");
println first4.number + ' ' + first4.name
println first4.NumberX2()
first4.numInt(null)
//firstClass4.numint(null) // int - Error
println()

BigDecimal BD1 = new BigDecimal(15)
BigDecimal BD2 = new BigDecimal(15)
println BD1.equals(BD2)
println BD1 == BD2
println()

BD1 = BD1.add(BD2)
println BD1
BD1 = BD1.divide(BD2)
println BD1
BD1 = BD1.multiply(BD2)
println BD1
println()
BD1 = BD1 + BD2
println BD1
BD1 = BD1 / BD2
println BD1
BD1 = BD1 * BD2
println BD1
println()

def var1 = 10
println var1.getClass().getName()
var1 = 'f'
println var1.getClass().getName()
var1 = 'First'
println var1.getClass().getName()
println()
def var2 = 'f'
println var2.getClass().getName()
var2 = 10
println var2.getClass().getName()
var2 = 'First'
println var2.getClass().getName()
println()
def var3 = 'First'
println var3.getClass().getName()
var3 = 'f'
println var3.getClass().getName()
var3 = 10
println var3.getClass().getName()

Date date1 = new Date(115, 1, 28)
Date date2 = new Date(115, 0, 31)
println date1 - date2
println date1
date1[Calendar.MONTH] -= 1
println date1
date1 += 1
date1[Calendar.MONTH] += 1
println date1

Closure closure1 = { a, b -> return a / b }
Closure closure2 = { d, c -> return d - c }
Closure closure3 = { a, b, c -> return closure2(closure1(a, b), c) }
println closure1.call(654, 123)
println closure2.call(7, 4)
println closure3.call(1, 2, 3)