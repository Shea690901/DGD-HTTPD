# include "support/tests.h"
# include "../include/www.h"
# include "../include/object.h"

inherit test LUNIT+"lib/testcase";

static void create()
{
	test::create("uri");
	add_test("testURI");
	add_test("testURI2");
	add_test("testURI3");
}


void setup()
{
}


void teardown()
{
}


/* The tests */

# define NEW() new_object(HTTP_URI);
void testURI()
{
	Uri uri;

	uri = NEW();
	uri->set("http://foo-bar.xs4all.nl:81/index.lsp?foo=1#sect",
			"/usr/www/webroot/");
	assert_equals( "/usr/www/webroot/",	uri->get_absolute_path()	);
	assert_equals( "",					uri->get_relative_path()	);
	assert_equals( "http",				uri->get_scheme()			);
	assert_equals( "foo-bar.xs4all.nl",	uri->get_authority()		);
	assert_equals( 81,					uri->get_port()				);
	assert_equals( "index.lsp",			uri->get_filename()			);
	assert_equals( "lsp",				uri->get_filesuffix()		);
	assert_equals( "foo=1",				uri->get_query_string()		);
	assert_equals( "sect",				uri->get_fragment()			);
}


void testURI2()
{
	Uri uri;

	uri = NEW();
	uri->set("/index.lsp?foo=1#sect", "/usr/www/webroot/");
	assert_equals( "/usr/www/webroot/",	uri->get_absolute_path()	);
	assert_equals( "",					uri->get_relative_path()	);
	assert_equals( "",					uri->get_scheme()			);
	assert_equals( "",					uri->get_authority()		);
	assert_equals( 80,					uri->get_port()				);
	assert_equals( "index.lsp",			uri->get_filename()			);
	assert_equals( "lsp",				uri->get_filesuffix()		);
	assert_equals( "foo=1",				uri->get_query_string()		);
	assert_equals( "sect",				uri->get_fragment()			);
}

void testURI3()
{
	Uri uri;

	uri = NEW();
	uri->set("/a%20test%20dir%20with%20a%20plus%20at%20the%20end%2B/" +
			"request.html?test=%20%2bx+y", "/usr/www/webroot/");
	assert_equals("a test dir with a plus at the end+/", uri->get_relative_path());
	assert_equals("request.html", uri->get_filename());
	assert_equals("test= +x y", uri->get_query_string());
}
