#include "IndexArchiveReader.h"

#include "FileIo.h"
#include "IndexDb.h"

namespace indexdb {

IndexArchiveReader::IndexArchiveReader(const std::string &path) : m_path(path)
{
    UnmappedReader reader(path);
    reader.readSignature(kIndexArchiveSignature);
    uint32_t entryCount = reader.readUInt32();
    for (uint32_t i = 0; i < entryCount; ++i) {
        Entry *entry = new Entry;
        entry->name = reader.readString();
        entry->hash = reader.readString();
        entry->fileOffset = reader.readUInt32(); // TODO: use 64-bit
        entry->fileLength = reader.readUInt32(); // TODO: use 64-bit
        m_entryMap[entry->name] = m_entries.size();
        m_entries.push_back(entry);
    }
}

IndexArchiveReader::~IndexArchiveReader()
{
    for (Entry *entry : m_entries)
        delete entry;
}

int IndexArchiveReader::size()
{
    return m_entries.size();
}

const IndexArchiveReader::Entry &IndexArchiveReader::entry(int index)
{
    return *m_entries[index];
}

int IndexArchiveReader::indexOf(const std::string &entryName)
{
    auto it = m_entryMap.find(entryName);
    return (it != m_entryMap.end()) ? it->second : -1;
}

Index *IndexArchiveReader::openEntry(int index)
{
    MappedReader *reader = new MappedReader(
                m_path,
                m_entries[index]->fileOffset,
                m_entries[index]->fileLength);
    return new Index(reader);
}

} // namespace indexdb
