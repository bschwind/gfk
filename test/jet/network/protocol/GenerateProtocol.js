var fs = require("fs");

var namespace = "jetGame";
var className = "Packet";

function endsWith(str, suffix) {
    return str.indexOf(suffix, str.length - suffix.length) !== -1;
}

var outputDirectory = process.argv[2];

if (!outputDirectory) {
	outputDirectory = "./";
}

if (!endsWith(outputDirectory, "/")) {
	outputDirectory += "/";
}

var typeToCPPType = {
	"bool" : "bool",
	"uint8" : "unsigned char",
	"uint16" : "unsigned short",
	"uint32" : "unsigned int",
	"uint64" : "unsigned long long int",
	"int8" : "char",
	"int16" : "short",
	"int32" : "int",
	"int64" : "signed long long int",
	"float32" : "float",
	"float64" : "double",
	"vector2" : "Vector2",
	"vector3" : "Vector3",
	"quaternion" : "Quaternion"
};

var typeToWriteFunction = {
	"uint8" : "WriteUnsignedByte",
	"uint16" : "WriteUnsignedInt16",
	"uint32" : "WriteUnsignedInt32",
	"uint64" : "WriteUnsignedInt64",
	"int8" : "WriteSignedByte",
	"int16" : "WriteSignedInt16",
	"int32" : "WriteSignedInt32",
	"int64" : "WriteSignedInt64",
	"float32" : "WriteFloat32",
	"float64" : "WriteFloat64",
	"vector2" : "WriteVector2",
	"vector3" : "WriteVector3",
	"quaternion" : "WriteQuaternion"
};

var typeToReadFunction = {
	"uint8" : "ReadUnsignedByte",
	"uint16" : "ReadUnsignedInt16",
	"uint32" : "ReadUnsignedInt32",
	"uint64" : "ReadUnsignedInt64",
	"int8" : "ReadSignedByte",
	"int16" : "ReadSignedInt16",
	"int32" : "ReadSignedInt32",
	"int64" : "ReadSignedInt64",
	"float32" : "ReadFloat32",
	"float64" : "ReadFloat64",
	"vector2" : "ReadVector2",
	"vector3" : "ReadVector3",
	"quaternion" : "ReadQuaternion"
};

function replaceAll(text, find, replace) {
	return text.replace(new RegExp(find, 'g'), replace);
}

// Converts a value like "GAME_INPUT_REQ" to "GameInputReq"
function enumToClassName(enumVal) {
	return enumVal.split("_")
	.map(function(word) {
		return word[0].toUpperCase() + word.substring(1).toLowerCase();
	}).join("");
}

function getFieldsArray(protocol) {
	var fields = [];
	for (var property in protocol) {
		if (protocol.hasOwnProperty(property)) {
			if (property !== "name") {
				// This is a field
				fields.push({name: property, type: protocol[property]});
			}
		}
	}

	return fields;
}

function getConstructorParametersString(fields) {
	return fields.map(function(field) {
		return typeToCPPType[field.type] + " " + field.name;
	}).join(", ");
}

function generateFieldDeclarations(protocol) {
	var fields = getFieldsArray(protocol);

	var result = fields.map(function(field) {
		return typeToCPPType[field.type] + " " + field.name + ";";
	});

	return result.length > 0 ? result.join("\n\t") + "\n\n\t" : "";
}

// Given a protocol, generate its class header declaration
function generateClassHeaderDeclaration(protocol) {
	var protocolClassName = protocol;

	var template = fs.readFileSync("ClassHeaderTemplate.txt").toString();

	template = replaceAll(template, "{PROTOCOL_CLASS_NAME}", enumToClassName(protocol.name));
	template = replaceAll(template, "{CLASS_NAME}", className);
	template = replaceAll(template, "{FIELDS}", generateFieldDeclarations(protocol));
	template = replaceAll(template, "{CONSTRUCTOR_PARAMETERS}", getConstructorParametersString(getFieldsArray(protocol)));

	return template;
}

function generateProtocolConstants(protocols) {
	return protocols.map(function(protocol, i) {
		return "static const unsigned short " + protocol.name + " = " + i + ";";
	}).join("\n\t");
}

function generateHeaderFile(inputData) {
	var template = fs.readFileSync("HeaderTemplate.txt").toString();

	template = replaceAll(template, "{CLASS_NAME}", className);
	template = replaceAll(template, "{NAMESPACE}", namespace);
	template = replaceAll(template, "{PACKET_TYPES}", generateProtocolConstants(inputData.protocols));
	template = replaceAll(template, "{CLASS_DECLARATIONS}", inputData.protocols.map(generateClassHeaderDeclaration).join("\n\n"));

	return template;
}

function fieldIsNonBoolean(field) {
	return !fieldIsBoolean(field);
}

function fieldIsBoolean(field) {
	return field.type === "bool";
}

// Given a count of boolean elements, determine the smallest
// possible type that can fit them all
function determineBitfieldType(count) {
	if (count <= 8) {
		return "uint8";
	} else if (count > 8 && count <= 16) {
		return "uint16";
	} else if (count > 16 && count <= 32) {
		return "uint32";
	} else if (count > 32 && count <= 64) {
		return "uint64";
	} else {
		console.error("The number of bools is too damn high!");
	}
}

function generateFieldWriteStatements(fields) {
	var writeStatements = fields
		.filter(fieldIsNonBoolean)
		.map(function(field) {
			return "buffer." + typeToWriteFunction[field.type] + "(" + field.name + ");";
		});

	var boolFieldCount = fields.filter(fieldIsBoolean).length;

	if (boolFieldCount > 0) {
		var bitfieldType = determineBitfieldType(boolFieldCount);
		writeStatements.push(typeToCPPType[bitfieldType] + " bitfield = 0;");
		fields
			.filter(fieldIsBoolean)
			.map(function(field, i) {
				return "bitfield |= (" + field.name + " ? (1 << " + i + ") : 0);";
			})
			.forEach(function(x) {
				writeStatements.push(x);
			});
		writeStatements.push("buffer." + typeToWriteFunction[bitfieldType] + "(bitfield);");
	}

	return writeStatements.length > 0 ? "\n\t" + writeStatements.join("\n\t") : "";
}

function generateFieldReadStatements(fields) {
	var readStatements = fields
		.filter(fieldIsNonBoolean)
		.map(function(field) {
			return typeToCPPType[field.type] + " " + field.name + " = buffer." + typeToReadFunction[field.type] + "();";
		});

	var boolFieldCount = fields.filter(fieldIsBoolean).length;

	if (boolFieldCount > 0) {
		var bitfieldType = determineBitfieldType(boolFieldCount);
		readStatements.push(typeToCPPType[bitfieldType] + " bitfield = buffer." + typeToReadFunction[bitfieldType] + "();");
		fields
			.filter(fieldIsBoolean)
			.map(function(field, i) {
				return typeToCPPType[field.type] + " " + field.name + " = bitfield & (1 << " + i + ");";
			})
			.forEach(function(x) {
				readStatements.push(x);
			});
	}
	
	return readStatements.length > 0 ? readStatements.join("\n\t") + "\n\t" : "";
}

function generateClassImplementation(protocol) {
	var template = fs.readFileSync("ClassImplementationTemplate.txt").toString();

	var fields = getFieldsArray(protocol);

	template = replaceAll(template, "{CLASS_NAME}", className);
	template = replaceAll(template, "{PROTOCOL_CLASS_NAME}", enumToClassName(protocol.name));
	template = replaceAll(template, "{PROTOCOL_NAME}", protocol.name);
	template = replaceAll(template, "{CONSTRUCTOR_PARAMETERS}", getConstructorParametersString(fields));
	template = replaceAll(template, "{PROTOCOL_DEFAULT_VALUES}", (fields.length > 0 ? ",\n" : "") + fields
		.map(function(field) {
			return field.name + "(" + field.name + ")";
		})
		.join(",\n"));
	template = replaceAll(template, "{WRITE_STATEMENTS}", generateFieldWriteStatements(fields));
	template = replaceAll(template, "{READ_STATEMENTS}", generateFieldReadStatements(fields));
	template = replaceAll(template, "{FIELD_LIST}", fields
		.map(function(field) {
			return field.name;
		})
		.join(", "));

	return template;
}

function generateImplementation(inputData) {
	var template = fs.readFileSync("SourceTemplate.txt").toString();

	template = replaceAll(template, "{CLASS_NAME}", className);
	template = replaceAll(template, "{NAMESPACE}", namespace);
	template = replaceAll(template, "{CLASS_IMPLEMENTATIONS}", inputData.protocols.map(generateClassImplementation).join("\n\n"));

	return template;
}

var inputData = fs.readFileSync("ExampleProtocol.json").toString();
inputData = JSON.parse(inputData);

var header = generateHeaderFile(inputData);
var implementation = generateImplementation(inputData);

// Write header and implementation to file
fs.writeFileSync(outputDirectory + className + ".hpp", header);
fs.writeFileSync(outputDirectory + className + ".cpp", implementation);
