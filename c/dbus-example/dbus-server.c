#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <dbus/dbus.h>
#include <dbus/dbus-glib-lowlevel.h>

const char *version = DBUS_SAMPLE_VERSION;
GMainLoop *main_loop;

const char *server_xml =
    DBUS_INTROSPECT_1_0_XML_DOCTYPE_DECL_NODE
    "<node>\n"

    "  <interface name='org.freedesktop.DBus.Introspectable'>\n"
    "    <method name='Introspect'>\n"
    "      <arg name='data' type='s' direction='out' />\n"
    "    </methode>\n"
    "  </interface>\n"

    "  <interface name='org.freedesktop.DBus.Properties'>\n"
    "    <method name='Get'>\n"
    "      <arg name='interface' type='s' direction='in' />\n"
    "      <arg name='property'  type='s' direction='in' />\n"
    "      <arg name='value'     type='s' direction='out' />\n"
    "    </method>\n"
    "    <method name='GetAll'>\n"
    "      <arg name='interface'  type='s' direction='in' />\n"
    "      <arg name='properties' type='s' direction='out' />\n"
    "    </method>\n"
    "  </interface>\n"

    "  <interface name='org.example.TestInterface'>\n"
    "    <property name='Version' type='s' access='read' />\n"
    "    <method name='Ping'>\n"
    "      <arg type='s' direction='out' />\n"
    "    </method>\n"
    "    <method name='Echo'>\n"
    "      <arg name='string' type='s' direction='in' />\n"
    "      <arg type='s' direction='out' />\n"
    "    </method>\n"
    "    <method name='Quit'>\n"
    "    </method>\n"
    "    <method name='EmitSignal'>\n"
    "    </method>\n"
    "    <signal name='OnEmitSignal'>\n"
    "    </signal>\n"
    "  </interface>\n"

    "</node>\n";

DBusHandlerResult server_message_handler(DBusConnection *conn, DBusMessage *msg, void *data) {
    DBusHandlerResult result;

    return result;
}

const DBusObjectPathVTable server_vtable = {
    .message_function = server_message_handler
};

int main(int argc, char **argv) {
    DBusConnection *conn;
    DBusError err;
    int rc;

    printf("Hello World from dbus-server\n");

    dbus_error_init(&err);

    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
    if (!conn) {
        fprintf(stderr, "Failed to get a dbus session %s\n", err.message);
        goto fail;
    }

    rc = dbus_bus_request_name(conn, "org.example.TestServer", DBUS_NAME_FLAG_REPLACE_EXISTING,
            &err);
    if (rc != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
        fprintf(stderr, "Failed to request name on bus %s\n", err.message);
        goto fail;
    }

    rc = dbus_connection_register_object_path(conn, "/org/example/TestObject", &server_vtable, 
            NULL);
    if (!rc) {
        fprintf(stderr, "Failed to register a object path for 'TestObject'\n");
        goto fail;
    }

    return EXIT_SUCCESS;

fail:
    dbus_error_free(&err);
    return EXIT_FAILURE;
}
