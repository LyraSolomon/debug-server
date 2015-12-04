cc_binary(
	name = "main",
	srcs = glob(["**/*.cpp"]),
	deps = ["//vision","//server"],
	linkopts = ["-lpthread"],
	visibility = ["//visibility:public"]
)