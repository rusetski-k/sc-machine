#include "Precompiled.hpp"
#include "Cache.hpp"
#include "Sha256.hpp"

#include <fstream>
#include <streambuf>

SourceCache::SourceCache(std::string const & path, std::string const & targetName)
	: m_cacheFileName(path + "/" + targetName + ".gen_cache")
{
}

SourceCache::~SourceCache()
{
}

void SourceCache::Load()
{
	std::ifstream input(m_cacheFileName);
	std::string str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

	size_t pos = str.find("\n");
	while (pos != std::string::npos)
	{
		std::string const line = str.substr(0, pos);

		size_t delimPos = line.find("|");
		if (delimPos != std::string::npos)
		{
			std::string key = line.substr(0, delimPos);
			std::string value = line.substr(delimPos + 1);

			if (!key.empty() && !value.empty())
				m_cache[key] = value;
		}

		str = str.substr(pos + 1);
		pos = str.find("\n");
	}
}

void SourceCache::Save()
{
	std::ofstream out(m_cacheFileName, std::fstream::out);
	tCacheMap::const_iterator it = m_cache.begin();
	for (; it != m_cache.end(); ++it)
	{
		out << it->first << "|" << it->second << std::endl;
	}
	out.flush();
	out.close();
}

void SourceCache::CheckGenerator(std::string const & fileName)
{
	std::string checksum = FileChecksum(fileName);

	tCacheMap::iterator it = m_cache.find(fileName);
	if (it != m_cache.end())
	{
		if (it->second == checksum)
			return; // generator doesn't changed
	}

	// clear cache, because of new generator
	m_cache.clear();
	m_cache[fileName] = checksum;
}

bool SourceCache::RequestGenerate(std::string const & fileName)
{
	std::string checksum = FileChecksum(fileName);
	
	tCacheMap::iterator it = m_cache.find(fileName);
	if (it != m_cache.end())
	{
		if (it->second == checksum)
			return false;
	}

	m_cache[fileName] = checksum;

	return true;
}

std::string SourceCache::FileChecksum(std::string const & fileName)
{
	std::ifstream input(fileName);
	std::string str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());

	return sha256(str);
}