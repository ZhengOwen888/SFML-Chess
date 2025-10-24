cmake_minimum_required(VERSION 3.23)

# collect game render files
file(GLOB_RECURSE GAME_RENDER_SRC
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# create GameRender static library
add_library(GameRender STATIC ${GAME_RENDER_SRC})

# include directory for GameRender headers
target_include_directories(GameRender
	PUBLIC
		"${CMAKE_SOURCE_DIR}/include/game_render"
)
