# Oparse

A model binding library for Orbiter cfg files. It is designed to let you bind values from cfg files to fields in your classes and validate them with as comfortable a syntax as I could manage.
This isn't Jackson however, since C++ isn't Java and doesn't support any kind of reflection, so unfortunately you still have to define the bindings yourself.

## Why should I use Oparse?

Oparse has enabled me to replace over a thousand lines of parsing code with barely a hundred lines of mostly logicless mappings in a large orbiter add-on, and will save me many hundred more as the project continues. It can do the same for you. That is, if you *have* that much parsing code in your project. Which you probably don't. So admittedly you won't have much use for it. But hey, should you ever find yourself taking on an Orbiter add-on that happens to have tons of data in external files, it's here for you to use.  
It is also no problem to use Oparse without linking the orbiter sdk using #def OPARSE_STANDALONE, which means that if you structure your code correctly you can reuse your models in other projects. Of course, again, most people won't have a use for that, but there you have it.

## How to include Oparse in your project

* Clone the repository into your OrbiterSDK folder.
* Add Oparse/include to your include folders.
* Add Oparse/lib to your library folders.
* Add Oparse_Debug.lib, Oparse_Release.lib, Oparse_Standalone_Debug.lib or Oparse_Standalone_Release.lib to your project dependencies.
* If you are using one of the standalone libraries, make sure to add #def OPARSE_STANDALONE to your project.

Libraries are built in VS 2017, so if you're using another version, you might have to rebuild. If you cloned Oparse into the orbitersdk folder this should work without issues, if not you will have to change the include and library paths for the orbiter sdk in the project settings.

## Quick and dirty usage

This is just a quick and dirty example to give you an impression of what to expect. There's an example project included in the source code that demonstrates most features in action.

For those who are not in the know,  a model is an object containing only data and no logic. 
While it is possible to map directly to properties of your VESSEL class, I'd really not recommend it, especially if you want to also use Oparse for scenario serialisation and deserialisation. Because the data you need in your scenario is usually not the same you need in your config file.
A simple model might look like this:

```
// MYVESSELDATA.h
#include "OpForwardDeclare.h"

struct MYVESSELDATA
{
public:
	string GetName() { return name; };
	double GetLength() { return length; };
	VECTOR3 GetCoG() { return cog; };

	Oparse::OpModelDef GetModelDef();

private:
	string name = "defaultname";
	double length = 10;
	VECTOR3 cog;
}
```
```
// MYVESSELDATA.cpp
#include "OpStdLibs.h"
#include "Oparse.h"
using namespace Oparse;

OpModelDef MYVESSELDATA::GetModelDef()
{
	return OpModelDef() = {
		{ "name", { _Param(name), {} } },
		{ "length", { _Param(length), {} } },
		{ "CoG", { _Param(cog), { _REQUIRED() } } }
	};
}
```
Of note here is that I sepparated the actual calls to Oparse into the cpp file. This is not mandatory, but it allows you to only include OpForwardDeclare 
in your main build path, which will give you all the declarations you need to use a model in other classes, while the overhead of including Oparse.h can be left to files that actually need it.  
Also note that if you include Oparse, you get everything you need, *except* for the standard libraries used by Oparse. Many people will already have them in their main build path, but if not, you can include "OpStdLibs.h".

In any case, below you see how to use the model to parse your config file in your Orbiter add-on.
This example assumes that your vessel has a property MYVESSELDATA data.
```
void VESSEL2::clbkSetClassCaps(FILEHANDLE  cfg)
{
	PARSINGRESULT result = ParseFile(cfg, data.GetModelDef(), "myvessel.cfg");
} 
```
There, that's it. All data defined in your mapping has now been parsed into a data structure that you can easily access in your code.
In case you're wondering why I'm passing a filename additionally to the FILEHANDLE, it's purely for loggin purposes.
You can use the PARSINGRESULT to generate a formatted string message containing all the errors, and specifying a filename here will conveniently add it to that message, which makes for much more comprehensible logging.

The config file for this example might look something like this:
```
module = MyVessel

name = Inevitable Obsolesnece
length = 20
cog = 0 0 -2

.
.
;some more orbiter parameters
```


## Core concepts

Oparse lets you map parameter names to class properties of your model via references and bundle it with a list of validators. More precisely, you map a parameter name to a parser instance that you load with a reference to the property you want to receive the value, and a vector of validators for that value. There are parsers for several primitive types as well as more complex ones like lists, blocks and nested models.
Most of these same parsers are also able to convert the bound value back to cfg syntax, so Oparse can also be used for serialisation within certain limitations. Since there is not really a hard standard for the Orbiter cfg synthax, I have tried to implement what exists and expand on it in what I consider a mostly logical and consistent way, but YMMV. For more information on what parsers and validators are available, what types they support and what their respective cfg synthax looks like, see the sections "Available Parsers" and "Available Validators".
Apart from that, Oparse also offers a set of validators to help you formulate more precise specifications for your data.

Parsers are objects that you create by invoking a factory function. They live on the heap, but their destruction is handled by Oparse after their data has been parsed and validated. The usual way to map a model is to add a GetModelDef() method to the your model class that creates the map. Note that this does *not* mean that models need to inherit a certain base class. They are handled in a generic way.


## Notes on cfg syntax

### Special note on VECTOR3
VECTOR3 is a very common datatype in Orbiter, and as such directly supported by Oparse, even when using a standalone library without the orbiter sdk in the build path. The standard delimiter for the individual values of a VECTOR3 in cfg files is the space. Which is not the luckiest choice imho, but I kept it. Note that for any kind of lists involving VECTOR3, this means that space *cannot* be used as a delimiter for the list elements, as Oparse uses a divide and conquer strategy to split strings into individual values. Tab is still ok, though.

### cfgs, spaces and tabs
Spaces and tabs are different characters, and are considered unique and unrelated by Oparse. So a list with spaces as a delimiter will throw errors if it is instead separated by tabs. There is one exception to this rule, which I added for convenience and readability: Any four consecutive spaces will be considered a tab by Oparse.

### cfg blocks
Orbiter cfg files have the convention of "Blocks", that start with a *BEGIN_BLOCKNAME* and end with an *END_BLOCKNAME* statement. Oparse uses this convention for any kind of nested data like BlockList or Models (see list below). Oparse treats the BEGIN_ part of the statement as beginning of the block, while it treats the BLOCKNAME part as the parameter name being mapped to. 
It also supports some synthax sugar for blocks with spaces in their name. The whole rest of the line following BEGIN_ will be used to identify the mapped parameters (excluding comments).
This means that Blocknames may contain spaces, something normal parameter names may not. In the closing statement however, only the part of the blockname in front of the space is considered. This means that a block can be started with e.g. *BEGIN_MODELDATA ONE*, and closed with *END_MODELDATA*, making for less typing.

### Comments
Orbiter uses the semicolon ; to mark comments, and Oparse respects this notation. Any data that follows after a semicolon will not be parsed. There is no syntax for block comments, I'm afraid.


## Available Parsers
Below is a list of the available parser factories and what types they support.  
For simplicity, all syntax examples in ths section are kept minimal and do not contain validators.

### _Param(&receiver)
Binds a simple config parameter to a variable.   
__config syntax:__  
```
foo = bar
```
__Oparse syntax:__  
```
{ "foo", Param(myStringProperty), {} } 
```
__supported types for receiver:__  
> int, float, double, bool, string, VECTOR3  


### _List(&receiver, delimiter)
Fills a vector with a series of values separated by a specifiable delimiter.
__config syntax:__  
```
foo = 1, 2, 3, 4, 5 ...
```
__Oparse syntax:__  
```
{ "foo", _List(myIntVector), {} }
```
__supported types for receiver:__  
> vector\<int\>, vector\<float\>, vector\<double\>, vector\<bool\>, vector\<string\>, vector\<VECTOR3\>


### _MixedList(OpValues receivers, delimiter)
A Mixed list is a list of *determinate* length, in which every element may have another Type. 
A good example for this would be the way Orbiter expects an individual Attachmentpoint to be defined.
The individual values in a MixedList are defined by _Param parsers, and may have individual validators.  
__config syntax:__  
```
foo = 1 2 3, is not, 1.0, 2.0, 3.0, that would be, false
```
__Oparse syntax:__  
```
{ "foo", { _MixedList(OpValues() = {
            { _Param(someVECTOR3), {} },
            { _Param(someString), {} },
            { _Param(float1), {} },
            { _Param(float2), {} },
            { _Param(float3), {} },
            { _Param(anotherString), {} },
            { _Param(aBoolean), {} }
        }, ",")
}};
```
__supported types:__  
A MixedList takes an instance of type OpValues, which is a vector of pairs that map a _Param to a list of validators. 
As such, elements of a MixedList can have any type that _Param supports.
__Note:__  
The _REQUIRED() validator does not work on elements of a MixedList and will always fail, so don't use it.
You don't need it anyways, since you will receive formatting errors if the list doesn't match the mapping.


### _BlockList<T>(&receiver)
A BlockList is a list of MixedLists in a block statement, with each MixedList being on its own line. 
A Blocklist binds to a vector pointers of any class, as long as that class provides a method with the signature `OpMixedList *GetMapping()`.  
__config syntax:__  
```
BEGIN_FOO
	1 2 3, is not, 1.0, 2.0, 3.0, that would be, false
	1 2 3, is certainly not, 1.5, 2.5, 3.5, that is, true
END_FOO
```
__Oparse syntax:__  
```
{ "foo", _BlockList<MyMixedList>(myMixedListVector), {} } 
```
__supported types for receiver:__  
> vector\<T*\>, where class T implements a function with the signature OpMixedList *GetMapping().


### _Model<T>(&receiver)
A Model is a class that (very preferably) exists for the sole purpose of storing data.
The only condition for a valid Oparse model is that it implements a method with the signature OpModelDef GetModelDef();  
__config syntax:__    
```
BEGIN_FOO
	foo = this is a nested block
	bar = any syntax valid inside a cfg is also valid inside a model block
END_FOO
```
__Oparse syntax:__  
```
{ "foo", _Model<MyModel>(myModelInstance), {} } 
```
__supported types for receiver:__  
> T, T*, where class T implements a method with the signature OpModelDef GetModelDef();


### _ModelFactory<T, U(optional)>(&receiver)
A parser that will create new model instances and fill a passed vector with pointers to them.
Supports polymorphism by letting you define the type of the base class of the models in U.
Note that while T must provide a method with the signature OpModelDef GetModelDef(), there is no such requirement for U.  
__config syntax:__    
The following with above definition will result in myModelVector containing two instaces of type MyModel*:
```
BEGIN_FOO
	bar = this is the first instance
END_FOO

BEGIN_FOO
	bar = this is the second instance
END_FOO
```
__Oparse syntax:__  
```
{ "foo", _ModelFactory<MyModel>(myModelVector), {} }
```
__supported types for receiver:__  
vector\<T*\> if only T is given, or vector\<U*\> where T inherits U when T and U are given. T has to implement a method with the signature OpModelDef GetModelDef();
__Notes on polymorphism:__  
When using polymorphism, it is a typical case to map different parameters to the same vector, like so:
```
vector<MyModelBase*> receiver;
{
	{ "MyModelBase foo", _ModelFactory<MyModelFoo, MyModelBase>(receiver), {} },
	{ "MyModelBase bar", _ModelFactory<MyModelBar, MyModelBase>(receiver), {} }
}
```
In this case, both ModelFactories will add elements to the same receiver, which ends up with multiple objects of type MyModelFoo* as well as MyModelBar*.
Since both inherit from MyModelBase, this is not a problem.


### _Lambda(function<string(string)>, function<string()>(optional))
A parameter parser for those moments when the shoe just won't fit. 
It lets you pass a lambda function that receives the value of the parameter as a string and expects a string with an error message in return.
In the desirable case of there not being any errors, just return an empty string.
Optionally, you can also pass a lambda function that just returns a string as a second argument. If it is present, it will be used for serialisation.  
__config syntax__  
```
foo = this is kind of pointless.
```
__Oparse syntax:__  
This example with the below config parameter will result in myvar containing the phrase "this is kind of pointless. What would you have done to demonstrate this?".
```
{ "foo", _Lambda([&](string value) {
		myvar = value + " What would you have done to demonstrate this?";
		return "";
	}), {}
}
```
__supported types for receiver:__  
A Lambda parser does not actually map to a receiver. It just passes you the parsed string belonging to a parameter. 
What you do with it and what you assign it to is completely up to you.
__Note:__  
Lambda parsers can *NOT* be validated!



## Available Validators
Model binding is really not that much help if you cannot also validate the data being parsed.
So Oparse allows you to define a list of validators for every individual value, like so:
```
{ "foo", _Param(myInt), { _REQUIRED(), MAX(5) } }
```
Validation errors will be contained in the PARSINGRESULT object returned by parsing operations. 
Oparse uses a best effort strategy, so unless there are structural problems with the parsed data that make it unable for Oparse
to make sense of it, it will read the entire data and present all validation errors at the end of it.

Take note that not all validators support all parsers, or might do different things depending on the parser being validated.
__!!Note that even if below documentation states that the Validator is applicable to any parser, this still excludes _Lambda!!__

### _REQUIRED()
Results in an error if the parameter was not present in the parsed data.  
__supported parsers:__  
Any, except parsers used inside a MixedList. In this case, _REQUIRED() will *always* fail.


### _REQUIREDBY(string paramName, variable value)
Treats this parameter as required *if* another parameter has a certain value, but not otherwise.  
__supported types for value:__  
int, bool and string.  
__supported parsers:__  
Any, except parsers used inside a MixedList. In this case, _REQUIREDBY() will always fail if the condition is met.  

### _EXCLUDEDBY(string paramName)
Results in an error if both the maped parameter and the parameter passed to the validator are present.  
__supported parsers:__  
Any, except parsers used inside a MixedList.  

### _MAX(double maxValue)
Results in an error if the parsed value exceeds maxValue. In a _List, results in an error if *any* values in the list exceed maxValue.  
__supported parsers:__  
_Param and _List of type int, float and double.  

### _MIN(double minValue)
Results in an error if the parsed value is lower than minValue. In a _List, results in an error if *any* values in the list are lower than minValue.  
__supported parsers:__  
_Param and _List of type int, float and double.  

### _RANGE(double minValue, double maxValue)
Results in an error if the parsed value is not between minValue and maxValue. In a _List, results in an error if *any* values are not between minValue and maxValue.  
__supported parsers:__  
_Param and _List of type int, float and double.  

### _LENGTH(int maxLength)
Results in an error if the lenth of a string or a _List is longer than maxValue.  
__supported parsers:__  
_Param of type string, _List.  

### _LENGTH(int minLength, int maxLength)
Results in an error if the length of a string or a _List is less than minValue or longer than maxValue.  
__supported parsers:__  
_Param of type string, _List.  

### _ISANYOF(vector<string>allowedValues, bool caseSensitive = false)
Results in an error if a parsed string does not match any of the specified values.
Pass true for caseSensitive to enforce case sensitive comparison.  
__supported parameters:__  
_Param of type string.  



## Evaluating parsing results

Oparse follows a best-effort strategy when parsing your data, which means that as long as nothing is inherently wrong with the structure of the file, Oparse will attempt to read and validate all data, even if some of it contains errors.
All parsing calls will return a PARSIINGRESULT object. The PARSINGRESULT object will contain all errors encountered during parsing, so in most cases it will give you an immediate oversight of *everything* that's wrong with a file.

The errors are mapped to their respective parameter names so you can judge what is wrong where. Since this is quite frequently information that is not only interesting for the developer that defines tha mapping, but also for potentially unrelated parties that are just modfying config files, there's also a nice call to get all the errors in a neatly formatted string that can easily be logged. An example of what that might look like is in the next section.

The PARSINGRESULT object also provides warnings, but those only refer to validators that are unaplicable to a parser. Generally nothing bad will happen when a validator cannot be applied, but you should definitely try to keep your code clean.

## Loading data from scenario

When Orbiter loads a config file, it will already have read all the data that it is interested in, so there's no need to bother with parameters that were not mapped to you model.  
When loading data from a scenario, things look quite a bit different, though. Here you are expected to forward lines that you are not using yourself to the VESSEL base class. The PARSINGRESULT provides the means to do that, by storing all lines it has no mapping for in a list.

So if you are loading data from a scenario, you can let Oparse do its job, and comfortably forward all those lines when you're done, like so:
```
void MyVessel::clbkLoadStateEx(FILEHANDLE scn, void *status)
{
	PARSINGRESULT result = ParseFile(scn, myScenarioData.GetModelDef(), "myvessel.cfg");
	
	if (result.HasErrors())
	{
		oapiWriteLog((char*)result.GetFormattedErrorsForFile());
		throw runtime_error("Errors in scenario data, see orbiter.log");
	}
	
	vector<string> unparsedLines = result.GetUnparsedLines();
	for (UINT i = 0; i < unparsedLines.size(); ++i)
	{
		ParseScenarioLineEx((char*)unparsedLines[i].data(), status);
	}
}

```

## ModelDefs and inheritance

It is really not recommended to use inheritance in your mappings. Polymorphic models are often a neccessity for dynamic construction and organisation, but in general you should not use it to create the *mapps themselves*. In other words, each model should provide a complete map with all its fields, and the GetModelDef() method should not be overriden from a base class. This can lead to some redundancy, but also results in much more comprehensive code.  
In some rare occasions, however, it can make sense that a base class provides a mapping for its own fields so the inheriting model doesn't need to bother. In essence, this means that the base class stores most of the data, and the inheriting models have only some additional fields.  
If you have a case where you are convinced that this structure is more comprehensive, you can use the Oparse::MergeModelDef() function. Its usage would look like this:
```
class SomeBaseData
{
public:
	string field1;
	double field2;
	VECTOR3 field3;

	virtual Oparse::OpModelDef GetModelDef()
	{
		return OpModelDef() = {
			{ "field1", { _Param(field1), {} } },
			{ "field2", { _Param(field2), {} } },
			{ "field3", { _Param(field3), {} } }
		}
	};
}

class SomeSpecialisedData : public SomeBaseData
{
public:
	string specialField1;
	string specialField2;

	Oparse:: OpModelDef GetModelDef()
	{
		return MergeModelDefs(
			SomeBaseData::GetModelDef(),
			OpModelDef() = {
				{ "specialField1", { _Param(specialField1), {} } },
				{ "specialField2", { _Param(specialField2), {} } },				
			};
		);
	};
}
```

__IMPORTANT!!__
Contrary to when parameters are parsed from data, MergeModelDef is *case sensitive*! In other words, "field1" and "Field1" would not be recognised as the same parameter and would not be merged, but one of them would never be parsed.

