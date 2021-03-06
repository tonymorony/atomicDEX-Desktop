/******************************************************************************
 * Copyright © 2013-2019 The Komodo Platform Developers.                      *
 *                                                                            *
 * See the AUTHORS, DEVELOPER-AGREEMENT and LICENSE files at                  *
 * the top-level directory of this distribution for the individual copyright  *
 * holder information and the developer policies on copyright and licensing.  *
 *                                                                            *
 * Unless otherwise agreed in a custom licensing agreement, no part of the    *
 * Komodo Platform software, including this file may be copied, modified,     *
 * propagated or distributed except according to the terms contained in the   *
 * LICENSE file                                                               *
 *                                                                            *
 * Removal or modification of this copyright notice is prohibited.            *
 *                                                                            *
 ******************************************************************************/

//! Project Headers
#include "atomic.dex.coins.config.hpp"

namespace atomic_dex
{
    void
    to_json(nlohmann::json& j, const electrum_server& cfg)
    {
        spdlog::debug("{} l{} f[{}]", __FUNCTION__, __LINE__, fs::path(__FILE__).filename().string());
        j["url"] = cfg.url;
        if (cfg.protocol.has_value())
        {
            j["protocol"] = cfg.protocol.value();
        }
        if (cfg.disable_cert_verification.has_value())
        {
            j["disable_cert_verification"] = cfg.disable_cert_verification.value();
        }
    }

    void
    from_json(const nlohmann::json& j, electrum_server& cfg)
    {
        spdlog::debug("{} l{} f[{}]", __FUNCTION__, __LINE__, fs::path(__FILE__).filename().string());
        if (j.count("protocol") == 1)
        {
            cfg.protocol = j.at("protocol").get<std::string>();
        }
        if (j.count("disable_cert_verification") == 1)
        {
            cfg.disable_cert_verification = j.at("disable_cert_verification").get<bool>();
        }
        j.at("url").get_to(cfg.url);
    }

    void
    from_json(const nlohmann::json& j, coin_config& cfg)
    {
        spdlog::debug("{} l{} f[{}]", __FUNCTION__, __LINE__, fs::path(__FILE__).filename().string());
        j.at("coin").get_to(cfg.ticker);
        j.at("name").get_to(cfg.name);
        j.at("type").get_to(cfg.type);
        if (j.count("electrum") > 0)
        {
            cfg.electrum_urls = j.at("electrum").get<std::vector<electrum_server>>();
        }
        if (j.count("eth_nodes") > 0)
        {
            cfg.eth_urls = j.at("eth_nodes").get<std::vector<std::string>>();
        }
        cfg.is_claimable         = j.count("is_claimable") > 0;
        cfg.minimal_claim_amount = cfg.is_claimable ? j.at("minimal_claim_amount").get<std::string>() : "0";
        j.at("active").get_to(cfg.active);
        j.at("currently_enabled").get_to(cfg.currently_enabled);
        j.at("coinpaprika_id").get_to(cfg.coinpaprika_id);
        j.at("is_erc_20").get_to(cfg.is_erc_20);
        j.at("explorer_url").get_to(cfg.explorer_url);
        if (j.contains("explorer_tx_url"))
        {
            j.at("explorer_tx_url").get_to(cfg.tx_uri);
        }
        if (j.contains("explorer_address_url"))
        {
            j.at("explorer_address_url").get_to(cfg.address_url);
        }
    }
} // namespace atomic_dex
