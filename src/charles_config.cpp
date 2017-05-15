#include "charles_config.h"

int CharlesConfig::loadConfig(const char *conf) {
    vector<string> lines;
    FILE *file = fopen(conf, "r");
    if (file == NULL) {
        charles_err("open file %s failed. (%s)", conf, strerror(errno));
        return -1;
    }

    char *line = NULL;
    size_t max_line = 0;
    while (-1 != getline(&line, &max_line, file)) {
        lines.push_back(string(line));
    }
    free(line);

    string config = stripComments(lines);
    stripSpaces(config);
    if (0 != parseJson(config))
        return -1;

    fclose(file);
    return 0;
}

string CharlesConfig::stripComments(vector<string> &lines) {
    string config = "";
    for (int i = 0; i < lines.size(); ++i) {
        size_t pos = lines[i].find('#');
        if (pos != string::npos)
            lines[i].erase(pos);
        config += lines[i];
    }

    return config;
}

int CharlesConfig::stripSpaces(string &config) {
    config.erase(std::remove(config.begin(), config.end(), ' '), config.end());
    config.erase(std::remove(config.begin(), config.end(), '\t'), config.end());
    config.erase(std::remove(config.begin(), config.end(), '\n'), config.end());

    return 0;
}

int CharlesConfig::parseJson(string &config) {
    json_tokener_error json_err;
    json_object *conf_json = json_tokener_parse_verbose(config.c_str(), &json_err);
    if (conf_json == NULL) {
        charles_err("Json parse error for %s (%s)", config.c_str(), json_tokener_error_desc(json_err));
        return -1;
    }

    json_object *null = json_object_object_get(conf_json, "null");
    
    printf("null is type null? %d\n", json_object_is_type(null, json_type_null));
    printf("null is type boolean? %d\n", json_object_is_type(null, json_type_boolean));
    printf("null is type object? %d\n", json_object_is_type(null, json_type_object));

    json_object *boolean = json_object_object_get(conf_json, "boolean");
    printf("boolean is type boolean? %d\n", json_object_is_type(boolean, json_type_boolean));
    printf("boolean value is %d\n", json_object_get_boolean(boolean));
    printf("boolean is type object? %d\n", json_object_is_type(boolean, json_type_object));

    json_object *doubleV = json_object_object_get(conf_json, "double");
    printf("double is type double? %d\n", json_object_is_type(doubleV, json_type_double));
    printf("double value is %lf\n", json_object_get_double(doubleV));
    printf("double is type object? %d\n", json_object_is_type(doubleV, json_type_object));

    json_object *intV = json_object_object_get(conf_json, "int");
    printf("int is type int? %d\n", json_object_is_type(intV, json_type_int));
    printf("int value is %d\n", json_object_get_int(intV));
    printf("int is type object? %d\n", json_object_is_type(intV, json_type_object));

    json_object *object = json_object_object_get(conf_json, "object");
    printf("object is type object? %d\n", json_object_is_type(object, json_type_object));

    json_object *array = json_object_object_get(conf_json, "array");
    printf("array is type array? %d\n", json_object_is_type(array, json_type_array));
    printf("array is type object? %d\n", json_object_is_type(array, json_type_object));

    json_object *stringV = json_object_object_get(conf_json, "string");
    if (stringV == NULL)
        printf("string obj is NULL\n");
    printf("string is type string? %d\n", json_object_is_type(stringV, json_type_string));
    const char *str = json_object_get_string(stringV);
    if (str == NULL) 
        printf("string is NULL\n");
    printf("string value is %s\n", json_object_get_string(stringV));
    printf("string is type object? %d\n", json_object_is_type(stringV, json_type_object));


    json_object_put(conf_json);
    return 0;
}
