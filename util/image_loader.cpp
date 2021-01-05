/**********************************************************************
 * Copyright (c) 2021, Filip Vasiljevic
 * All rights reserved.
 *
 * This file is subject to the terms and conditions of the BSD 2-Clause
 * License.  See the file LICENSE in the root directory of the Rinvid
 * repository for more details.
 **********************************************************************/

#include <cstdint>
#include <iostream>
#include <vector>

#include "extern/include/stb_image.h"

#include "util/include/image_loader.h"

bool load_image(const char* file_name, std::vector<std::uint8_t>& image_data, std::int32_t& width,
                std::int32_t& height)
{
    std::int32_t number_of_channels;

    std::uint8_t* data = stbi_load(file_name, &width, &height, &number_of_channels, STBI_rgb_alpha);

    if (data == NULL)
    {
        return false;
    }

    for (std::int32_t i{0}; i < width * height * number_of_channels; ++i)
    {
        image_data.push_back(data[i]);
    }

    stbi_image_free(data);

    return true;
}