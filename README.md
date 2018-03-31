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

Oparse additionally supports std::string and the Orbiter type VECTOR3.
These are wrapped by OpString and OpVector3 respectively, and can be created by using the factories _String and _Vector3,
again accepting a reference to the variable to bind to as an argument.
Note that convention in .cfg files for VECTOR3 seems to be using a space as delimiter between the values for the three axes,
which I find unfortunate, but I'm not going to break it. Space as delimiter for VECTOR3-fields is therefore hardcoded and cannot be changed.

__list types__

What's a parsing library without lists? Pretty useless, that's what it is. So Oparse supports two fundamentally different list types:
 * OpList, which is a list of indeterminate length where every element is of the same type. So, A very typical list.
 Lists can map to an std::vector of any of the data types mentioned above, and the delimiter between elements is modifiable on a list-by-list basis.
 They can be constructed with one of the _List factories.

 * OpMixedList, which is a list of *determinate* length, but every element can map to a different type. If you take a look at Orbiter cfg files,
 the declaration of attachment points is a typical example of this. It is one line with a string, followed by 3 VECTOR3s, followed by another string.
 A OpMixedList couldn't actually be used to parse attachment points, because they're inside a block, not assigned to a parameter, which will be explained further down.
 However, I' think you should get the picture what it's for. You can use the _MixedList factory to instantiate it, and use the OpValues typedef to pass your definition inline if you so wish.

 ### Examples

 comming soon.
