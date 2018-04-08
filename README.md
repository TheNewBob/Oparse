# Oparse

A model binding library for Orbiter cfg files.

## Project status

In mid development.

## Documentation

Oparse is designed to let you bind values from cfg files to fields in your classes and validate them with as comfortable a syntax as I could manage.
This isn't Jackson however, since C++ isn't Java and doesn't support any kind of reflection, so unfortunately you still have to define the bindings yourself.

### Supported data types

__primitives__

Oparse supports four basic primitives: int, float, double and bool. 
For mapping definition these are wrapped by the classes OpInt, OpFloat, OpDouble and OpBool respectively.
For easier construction in your maps you can use the factories _Int, _Float, _Double and _Bool, so you don't have to type new every time.
These factories take a reference to the variable they should bind to as an argument. It's all fairly self-explanatory once you look at the code samples below.

__non-primitve data types__

* OpString, which wraps an std::string. Note that ; and \n are reserved symbols in cfg files and can't be used in a string.
Appart from these two, any ASCII-symbol should be parsed as expected. I don't know exactly what'll happen if you throw UTF-8 in there, but it can't be good.
You can use the _String factory for quick mapping.

* OpVector3 maps to the Orbiter VECTOR3 struct.Unsurprisingly, it can be conveniently instantiated with _Vector3.
Note that convention in .cfg files for VECTOR3 seems to be using a space as delimiter between the values for the three axes,
which I find unfortunate, but I'm not going to break it. Space as delimiter for VECTOR3-fields is therefore hardcoded and cannot be changed.

__list types__

What's a parsing library without lists? Pretty useless, that's what it is. So Oparse supports three fundamentally different list types:

 * OpList, which is a list of indeterminate length where every element is of the same type. So, A very typical list.
 Lists can map to an std::vector of any of the data types mentioned above, and the delimiter between elements is modifiable on a list-by-list basis.
 They can be constructed with one of the _List factories.

 * OpMixedList, which is a list of *determinate* length, but every element can map to a different type. If you take a look at Orbiter cfg files,
 the declaration of attachment points is a typical example of this. It is one line with a string, followed by 3 VECTOR3s, followed by another string.
 Though An OpMixedList couldn't actually be used to parse attachment points, see OpBlockList below. You should however get a picture of what a MixedList is
 from this example.
 
 * OpBlockList, which is support for the cfg convention of blocks of values between a BEGIN_ and an END_ statement, as seen in dockport and attachment point definition. Those specifically are parsed by Orbiter itself so usually you don't have to, but this way of writing definitions can come in handy for other data.
 In effect, a BlockList is a list of MixedLists (see above). The _Block<T> factory is available for mapping to a reference of either an std::vector<T>,
 or an std::vector<T*>, depending on how you prefer the data to be allocated. Note that the class or struct provided must implement a method with the signature 
 `OpMixedList *GetMapping()` that will be used to map the cfg values to the newly created objects.

__models__

Actual model mapping (that is, the automatic binding of values to fields of a class) work based on inheritance.
You create a class that inherits OpModel, and you pass the mapping for your fields to the base baseclass in your constructor.
The base class is really just needed for unambiguous identification and contains almost no code, so don't worry about this bogging down your data classes.
There is no quick factory for OpModel, since you'r generally expected to have an instance ready.

Models are fully nestable. A field of one of your models can be another model, and as long as the key you give it matches the proper BEGIN_ block in the cfg
and you map a pointer to your nested instance to it, the binding will work without any further code from your side.

However, when things get really wild, you might not even _know_ which blocks will be declared in the config. Rather, you want to define the propperties of your vessel
based on the blocks that are declared.
For this extreme case, Oparse offers the OpModelFactory, a generic class that will _instantiate_ a model of the passed class and add it to a vector you pass it.
Kind of similar to what the BlockList does, just that it does it with whole models. OpModelFactories can be created with the _ModelFactory<T, U>(vector<U*>) quick factory,
in which T is the type of the model to be instantiated, and U is the type of the vector to receive it, so you can use polymorphic models with this.


 ### Validators

 comming soon.
 


 ### Examples

 comming soon.
