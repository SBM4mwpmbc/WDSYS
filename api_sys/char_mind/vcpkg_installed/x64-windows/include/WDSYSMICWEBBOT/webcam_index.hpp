#ifndef WEBCAM_INDEX_HPP
#define WEBCAM_INDEX_HPP

#include <stdio.h>
#include <string>
#include <opencv4/opencv2/opencv.hpp>

int test_camera_until_valid_frame(int indexx = 1, int target_frame = 35, int max_frames = 36)
{
    printf("CAMOPEN at index ", indexx, "..");
    cv::VideoCapture cap(indexx, cv::CAP_DSHOW);
    if (!cap.isOpened())
    {
        printf("Failed to open camera at index %d\n", indexx);
        return 1;
    }

    int valid_frame = NULL;
    int frame_count = 0;

    printf("CAPTURE TO: %d FRAMES::FIND VALID\n", max_frames);

    while (frame_count < max_frames)
    {
        bool ret = cap.read(frame);
        cv::Mat frame = cap.read();
        frame_count += 1;
        if (!ret)
        {
            printf("FRAME %d: CAPTURE ERR\n", frame_count);
            continue;
        }
        printf("FRAME %d: CAPTURED\n", frame_count);

        // check for target frame to show
        if (frame_count == target_frame)
        {
            valid_frame = frame;
            break;
        }
    }

    cap.release();

    if (!valid_frame.empty())
    {
        std::string window_name = "Valid Frame #" + std::to_string(target_frame);
        cv::imshow(window_name, valid_frame);
        printf("FRAME_SHW #%d, Q or close window for ext\n", target_frame);

        while (true)
        {
            if (cv::waitKey(100) & 0xFF == 'q')
            {
                break;
            }
            
            if (cv::getWindowProperty(window_name, cv::WND_PROP_VISIBLE) < 1)
            {
                break;
            }
        }

        cv::destroyAllWindows();
        // destory buzz lightyear for gods sake
    }
    else
    {
        printf("VLD FRAME NULL AT/BEFORE FRAME %d\n", max_frames);
    }

    return 0;
}

#endif