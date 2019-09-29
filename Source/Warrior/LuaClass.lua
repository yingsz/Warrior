"local getters = { }\
local setters = { }\
local indexfunc\
local gcfunc\
\
local classmeta = {\
	__index = function(tb, k)\
		local v = rawget(tb, k)\
		if v ~= nil then return v end\
		v = rawget(classmeta, k)\
		if v ~= nil then return v end\
		v = getters[k]\
		if v ~= nil then return v(tb) end\
		if indexfunc then return indexfunc(tb, k) end\
	end,\
	\
	__newindex = function(tb, k, v)\
		local func = setters[k]\
		if not func then \
			rawset(tb, k)\
		else\
			func(tb, v)\
		end\
	end,\
	\
	__gc = function(tb)\
		if gcfunc then gcfunc(tb) end\
	end\
}\
\
return classmeta"
