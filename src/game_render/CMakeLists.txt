cmake_minimum_required(VERSION 3.23)

# Collect game logic files
file(GLOB_RECURSE GAME_RENDER_SRC
	CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# Create GameLogic static library
add_library(GameRender STATIC ${GAME_RENDER_SRC})

# Include directory for GameLogic headers
target_include_directories(GameRender
	PUBLIC
		"${CMAKE_SOURCE_DIR}/include/game_render"
)
