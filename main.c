#include <stdio.h>

#include <gst/gst.h>
#include <gst/gstinfo.h>
#include <gst/rtsp-server/rtsp-server.h>

#define DEFAULT_RTSP_PORT       "8554"
#define DEFAULT_STREAM_NAME     "/Capture"

static char* port               = (char*)DEFAULT_RTSP_PORT;
static char* stream_name        = (char*)DEFAULT_STREAM_NAME;

static GOptionEntry entries[] = {
  
  {"port", 'p', 0, G_OPTION_ARG_STRING, &port, "Port to listen on (default: " DEFAULT_RTSP_PORT ")", "PORT"},
  {"stream", 's', 0, G_OPTION_ARG_STRING, &stream_name, "Stream Name (default: " DEFAULT_STREAM_NAME ")", "STREAM_NAME"},
  {NULL}
};

int main(int argc, char* argv[])
{
    gst_init(&argc, &argv);

    /*
    * enable debug print
    */
    /*
    if (true)
    {
        gst_debug_set_active(true);
        gst_debug_set_default_threshold(GST_LEVEL_LOG);
    }
    */

    GOptionContext* optctx;
    GError* error = NULL;
    GMainLoop* loop;
    GstRTSPServer* server;
    GstRTSPMountPoints* mounts;
    GstRTSPMediaFactory* factory;
    guint serverID;
    GstElement* pipeLine;

    optctx = g_option_context_new("<launch line> - Test RTSP Server, Launch\n\n"
        "Example: \"( videotestsrc ! x264enc ! rtph264pay name=pay0 pt=96 )\"");
    g_option_context_add_main_entries(optctx, entries, NULL);
    g_option_context_add_group(optctx, gst_init_get_option_group());
    if (!g_option_context_parse(optctx, &argc, &argv, &error)) {
        printf("Error parsing options: %s\n", error->message);
        g_option_context_free(optctx);
        g_clear_error(&error);
        return -1;
    }
    g_option_context_free(optctx);
    
    loop = g_main_loop_new(NULL, false);
    server = gst_rtsp_server_new();
 
    if (!server)
    {
        printf("[gst_rtsp_server_new] fail.\n");
        return -1;
    }

    /*
    * manaul set address
    */
    //gst_rtsp_server_set_address(server, ip);
    gst_rtsp_server_set_service(server, port);
    
    mounts = gst_rtsp_server_get_mount_points(server);
    factory = gst_rtsp_media_factory_new();

    char command[256] = { 0 };
    sprintf_s(command, "( dx9screencapsrc cursor=true monitor=0 ! videoconvert ! video/x-raw,format=I420,framerate=30/1 ! x264enc ! rtph264pay name=pay0 pt=96 )");
    //sprintf_s(command, "dx9screencapsrc cursor=true monitor=0 x=100 y=100 width=500 height=500 ! videoconvert ! video/x-raw,format=I420,framerate=30/1 ! x264enc ! rtph264pay name=pay0 pt=96");

    gst_rtsp_media_factory_set_launch(factory, command);
    gst_rtsp_media_factory_set_shared(factory, true);
    gst_rtsp_mount_points_add_factory(mounts, stream_name, factory);

    g_object_unref(mounts);
    serverID = gst_rtsp_server_attach(server, NULL);

    if (serverID == 0)
    {
        printf("[gst_rtsp_server_attach] fail.\n");
        return -1;
    }

    printf("stream ready at rtsp://127.0.0.1:%s%s\n", port, stream_name);

    g_main_loop_run(loop);

    return 0;
}
