#pragma once
#include <libpdbg.h>

#include <xyz/openbmc_project/Dump/Create/server.hpp>
#include <filesystem>
#include <sdbusplus/bus.hpp>
#include <sdbusplus/server/object.hpp>
#include <com/ibm/Dump/Create/server.hpp>

namespace openpower
{
namespace dump
{

constexpr auto DUMP_TMP_PATH = "/tmp/dump/";
constexpr auto SBE_DUMP_TYPE_HOSTBOOT = 0x5;
constexpr auto SBE_CLOCK_ON = 0x1;
constexpr auto SBE_CLOCK_OFF = 0x2;


using CreateIface = sdbusplus::server::object::object<
    sdbusplus::xyz::openbmc_project::Dump::server::Create>;

/** @class Manager
 *  @brief Dump  manager claa
 *  @details A concrete implementation for the
 *  xyz::openbmc_project::Dump::server::Create.
 */
class Manager : public CreateIface
{
  public:
    Manager() = delete;
    Manager(const Manager&) = default;
    Manager& operator=(const Manager&) = delete;
    Manager(Manager&&) = delete;
    Manager& operator=(Manager&&) = delete;
    virtual ~Manager() = default;

    /** @brief Constructor to put object onto bus at a dbus path.
     *  @param[in] bus - Bus to attach to.
     *  @param[in] path - Path of the service.
     */
    Manager(sdbusplus::bus::bus& bus, const char* path) :
        CreateIface(bus, path, true), bus(bus)
    {
    }

    /** @brief Implementation for CreateDump
     *  Method to request a host dump when there is an error related to host.
     *  @param[in] params - Parameters for creating the dump.
     *  
     *  @return object_path - The object path of the new dump entry.
     */
    sdbusplus::message::object_path
        createDump(std::map<std::string, std::string> params) override;

  private:
    /** @brief sdbusplus DBus bus connection. */
    sdbusplus::bus::bus& bus;

    /** @brief Method to find whether a processor is master
     *  @param[in] proc - pointer to processor target
     *
     *  @return bool - true if master processor else false.
     */
    bool isMasterProc(struct pdbg_target* proc);

    /** @brief The function to orchestrate dump collection from different
     *  sources
     *  @param type - Type of the dump
     *  @param id - A unique id assigned to dump to be collected
     *  @param errorLogId - Id of the error log associated with this collection
     */
    void collectDump(uint8_t type, uint32_t id, std::string errorLogId);

    /** @brief The function to collect dump from SBE
     *  @param[in] tgt - PIB target of the SBE to collect the dump.
     *  @param[in] dumpPath - Path of directory to write the dump files.
     *  @param[in] timestamp - Timestamp of collection
     *  @param[in] type - Type of the dump
     *  @param[in] clockState - State of the clock while collecting.
     */
    void collectDumpFromSBE(struct pdbg_target* tgt,
                            std::filesystem::path &dumpPath, uint64_t timestamp,
                            uint8_t type, uint8_t clockState);
};

} // namespace dump
} // namespace openpower