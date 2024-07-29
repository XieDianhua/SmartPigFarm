$(function() {

        var $fullText = $('.admin-fullText');
        $('#admin-fullscreen').on('click', function() {
            $.AMUI.fullscreen.toggle();
        });

        $(document).on($.AMUI.fullscreen.raw.fullscreenchange, function() {
            $fullText.text($.AMUI.fullscreen.isFullscreen ? '退出全屏' : '开启全屏');
        });


        var dataType = $('body').attr('data-type');
        for (key in pageData) {
            if (key == dataType) {
                pageData[key]();
            }
        }

        $('.tpl-switch').find('.tpl-switch-btn-view').on('click', function() {
            $(this).prev('.tpl-switch-btn').prop("checked", function() {
                    if ($(this).is(':checked')) {
                        return false
                    } else {
                        return true
                    }
                })
                // console.log('123123123')

        })
    })
    // ==========================
    // 侧边导航下拉列表
    // ==========================

$('.tpl-left-nav-link-list').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico').toggleClass('tpl-left-nav-more-ico-rotate');
    })
$('.tpl-left-nav-link-list1').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu1').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico1').toggleClass('tpl-left-nav-more-ico-rotate1');
    })
$('.tpl-left-nav-link-list2').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu2').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico2').toggleClass('tpl-left-nav-more-ico-rotate2');
    })
$('.tpl-left-nav-link-list3').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu3').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico3').toggleClass('tpl-left-nav-more-ico-rotate3');
    })
$('.tpl-left-nav-link-list4').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu4').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico4').toggleClass('tpl-left-nav-more-ico-rotate4');
    })
$('.tpl-left-nav-link-list5').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu5').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico5').toggleClass('tpl-left-nav-more-ico-rotate5');
    })
$('.tpl-left-nav-link-list6').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu6').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico6').toggleClass('tpl-left-nav-more-ico-rotate6');
    })
$('.tpl-left-nav-link-list7').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu7').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico7').toggleClass('tpl-left-nav-more-ico-rotate7');
    })
$('.tpl-left-nav-link-list8').on('click', function() {
        $(this).siblings('.tpl-left-nav-sub-menu8').slideToggle(80)
            .end()
            .find('.tpl-left-nav-more-ico8').toggleClass('tpl-left-nav-more-ico-rotate8');
    })
    // ==========================
    // 头部导航隐藏菜单
    // ==========================

$('.tpl-header-nav-hover-ico').on('click', function() {
    $('.tpl-left-nav').toggle();
    $('.tpl-content-wrapper').toggleClass('tpl-content-wrapper-hover');
})


// 页面数据
var pageData = {
    // ===============================================
    // 首页
    // ===============================================
    'index': function indexData() {


        var myScroll = new IScroll('#wrapper', {
            scrollbars: true,
            mouseWheel: true,
            interactiveScrollbars: true,
            shrinkScrollbars: 'scale',
            preventDefault: false,
            fadeScrollbars: true
        });

        var myScrollA = new IScroll('#wrapperA', {
            scrollbars: true,
            mouseWheel: true,
            interactiveScrollbars: true,
            shrinkScrollbars: 'scale',
            preventDefault: false,
            fadeScrollbars: true
        });

        var myScrollB = new IScroll('#wrapperB', {
            scrollbars: true,
            mouseWheel: true,
            interactiveScrollbars: true,
            shrinkScrollbars: 'scale',
            preventDefault: false,
            fadeScrollbars: true
        });



        // document.addEventListener('touchmove', function(e) { e.preventDefault(); }, false);

        // ==========================
        // 百度图表A http://echarts.baidu.com/
        // ==========================

        var echartsA = echarts.init(document.getElementById('tpl-echarts-A'));
        option = {

            tooltip: {
                trigger: 'axis',
            },
            legend: {
                data: ['温度', '湿度', '光照度']
            },
            grid: {
                left: '3%',
                right: '4%',
                bottom: '3%',
                containLabel: true
            },
            xAxis: [{
                type: 'category',
                boundaryGap: true,
                data: ['90m前', '75m前', '60m前', '45m前', '30m前', '15m前', '当前时间']
            }],

            yAxis: [{
                type: 'value'
            }],
            series: [{
                    name: '温度',
                    type: 'line',
                    // stack: '总量',
                    areaStyle: { normal: {} },
                    data: [120, 132, 101, 134, 90, 230, 210],
                    itemStyle: {
                        normal: {
                            color: '#a9aeea'
                        },
                        emphasis: {

                        }
                    }
                },
                {
                    name: '湿度',
                    type: 'line',
                    // stack: '总量',
                    areaStyle: { normal: {} },
                    data: [220, 182, 191, 234, 290, 330, 310],
                    itemStyle: {
                        normal: {
                            color: '#e7505a'
                        }
                    }
                },
                {
                    name: '光照度',
                    type: 'line',
                    // stack: '总量',
                    areaStyle: { normal: {} },
                    data: [150, 232, 201, 154, 190, 330, 410],
                    itemStyle: {
                        normal: {
                            color: '#32c5d2'
                        }
                    }
                }
            ]
        };
        echartsA.setOption(option);
    },
    // ===============================================
    // 图表页
    // ===============================================
    'chart': function chartData() {
        // ==========================
        // 百度图表A http://echarts.baidu.com/
        // ==========================

        var echartsC = echarts.init(document.getElementById('tpl-echarts-C'));


        optionC = {
            tooltip: {
                trigger: 'axis'
            },
            toolbox: {
                top: '0',
                feature: {
                    dataView: { show: true, readOnly: false },
                    magicType: { show: true, type: ['line', 'bar'] },
                    restore: { show: true },
                    saveAsImage: { show: true }
                }
            },
            title: {
                // text: '摸鱼时间到了'
            },
            legend: {
                data: ['消耗水量', '疫苗量', '消耗饲料']
            },
            xAxis: [{
                type: 'category',
                data: ['7月10', '7月11', '7月12', '7月13', '7月14', '7月15', '7月16', '7月17', '7月18', '7月19', '7月20', '7月21']
            }],
            yAxis: [{
                    type: 'value',
                    name: '体积',
                    min: 0,
                    max: 30,
                    interval: 5,
                    axisLabel: {
                        formatter: '{value} m³'
                    }
                },
                {
                    type: 'value',
                    name: '消耗饲料量',
                    min: 0,
                    max: 30,
                    interval: 5,
                    axisLabel: {
                        formatter: '{value} kg'
                    }
                }
            ],
            series: [{
                    name: '消耗水量',
                    type: 'bar',
                    data: [22.0, 24.9, 27.0, 23.2, 25.6, 26.7, 25.6, 22.2, 22.6, 20.0, 26.4, 23.3]
                },
                {
                    name: '疫苗量',
                    type: 'bar',
                    data: [2.0, 2.4, 1.9, 2.0, 1.6, 2.4, 1.9, 2.0, 1.8, 2.1, 2.0, 2.3]
                },
                {
                    name: '消耗饲料',
                    type: 'line',
                    yAxisIndex: 1,
                    data: [21, 19, 20, 18, 21, 25, 20, 27, 19, 21, 28, 25]
                }
            ]
        };

        echartsC.setOption(optionC);

        var echartsB = echarts.init(document.getElementById('tpl-echarts-B'));
        optionB = {
            tooltip: {
                trigger: 'axis'
            },
            legend: {
                x: 'center',
                data: ['某软件', '某主食手机', '某水果手机', '降水量', '蒸发量']
            },
            radar: [{
                    indicator: [
                        { text: '品牌', max: 100 },
                        { text: '内容', max: 100 },
                        { text: '可用性', max: 100 },
                        { text: '功能', max: 100 }
                    ],
                    center: ['25%', '40%'],
                    radius: 80
                },
                {
                    indicator: [
                        { text: '外观', max: 100 },
                        { text: '拍照', max: 100 },
                        { text: '系统', max: 100 },
                        { text: '性能', max: 100 },
                        { text: '屏幕', max: 100 }
                    ],
                    radius: 80,
                    center: ['50%', '60%'],
                },
                {
                    indicator: (function() {
                        var res = [];
                        for (var i = 1; i <= 12; i++) {
                            res.push({ text: i + '月', max: 100 });
                        }
                        return res;
                    })(),
                    center: ['75%', '40%'],
                    radius: 80
                }
            ],
            series: [{
                    type: 'radar',
                    tooltip: {
                        trigger: 'item'
                    },
                    itemStyle: { normal: { areaStyle: { type: 'default' } } },
                    data: [{
                        value: [60, 73, 85, 40],
                        name: '某软件'
                    }]
                },
                {
                    type: 'radar',
                    radarIndex: 1,
                    data: [{
                            value: [85, 90, 90, 95, 95],
                            name: '某主食手机'
                        },
                        {
                            value: [95, 80, 95, 90, 93],
                            name: '某水果手机'
                        }
                    ]
                },
                {
                    type: 'radar',
                    radarIndex: 2,
                    itemStyle: { normal: { areaStyle: { type: 'default' } } },
                    data: [{
                            name: '降水量',
                            value: [2.6, 5.9, 9.0, 26.4, 28.7, 70.7, 75.6, 82.2, 48.7, 18.8, 6.0, 2.3],
                        },
                        {
                            name: '蒸发量',
                            value: [2.0, 4.9, 7.0, 23.2, 25.6, 76.7, 35.6, 62.2, 32.6, 20.0, 6.4, 3.3]
                        }
                    ]
                }
            ]
        };
        echartsB.setOption(optionB);
        var echartsA = echarts.init(document.getElementById('tpl-echarts-A'));
        option = {
            title: {
                // text: '今天摸鱼时间',
                subtext: '真的很开心'
            },
            tooltip: {
                trigger: 'axis',

            },
            legend: {
                data: ['温度', '湿度', '光照度', '二氧化碳浓度', '氨气浓度', '硫化氢浓度']
            },
            toolbox: {
                show: true,
                feature: {
                    mark: { show: true },
                    dataView: { show: true, readOnly: false },
                    magicType: { show: true, type: ['line', 'bar', 'stack', 'tiled'] },
                    restore: { show: true },
                    saveAsImage: { show: true }
                }
            },
            calculable: true,
            grid: {
                left: '3%',
                right: '4%',
                bottom: '3%',
                containLabel: true
            },
            xAxis: [{
                type: 'category',
                boundaryGap: true,
                data: ['前90分钟', '前75分钟', '前60分钟', '前45分钟', '前30分钟', '前15分钟', '当前数据']
            }],

            yAxis: [{
                type: 'value',
                position: 'left',
                splitLine: { show: true },
                axisLine: {
                    show: false,

                    /*  lineStyle: {
                          color: '#E7E7E7'
                      }*/
                },
                axisLabel: {
                    show: true,
                    showMinLabel: true,
                    showMaxLabel: true,
                    formatter: '{value}'
                },
            }],
            series: [{
                    name: '温度',
                    type: 'line',
                    //stack: '总量',
                    areaStyle: { normal: {} },
                    data: [{ value: 31.5, name: '非温度', unit: '℃' }, { value: 32, name: '非温度', unit: '℃' }, { value: 31, name: '非温度', unit: '℃' }, { value: 30, name: '非温度', unit: '℃' }, { value: 30.5, name: '非温度', unit: '℃' }, { value: 31, name: '非温度', unit: '℃' }, { value: 29.5, name: '非温度', unit: '℃' }],
                    itemStyle: {
                        normal: {
                            color: '#19ae12'
                        },
                        // emphasis: {

                        // }
                    },
                    markPoint: {
                        data: [
                            { type: 'max', name: '最大值' },
                            { type: 'min', name: '最小值' }
                        ]
                    },
                    markLine: {
                        data: [
                            { type: 'average', name: '平均值' }
                        ]
                    }

                },
                {
                    name: '湿度',
                    type: 'line',
                    //stack: '总量',
                    areaStyle: { normal: {} },
                    data: [50, 55, 50, 45, 55, 50, 60],
                    itemStyle: {
                        normal: {
                            color: '#e7505a'
                        }
                    },
                    markPoint: {
                        data: [
                            { type: 'max', name: '最大值' },
                            { type: 'min', name: '最小值' }
                        ]
                    },
                    markLine: {
                        data: [
                            { type: 'average', name: '平均值' }
                        ]
                    }
                },
                {
                    name: '光照度',

                    type: 'line',
                    //stack: '总量',
                    areaStyle: { normal: {} },
                    data: [40, 50, 45, 50, 45, 60, 40],
                    itemStyle: {
                        normal: {
                            color: '#10c5d2'
                        }
                    },
                    markPoint: {
                        data: [
                            { type: 'max', name: '最大值' },
                            { type: 'min', name: '最小值' }
                        ]
                    },
                    markLine: {
                        data: [
                            { type: 'average', name: '平均值' }
                        ]
                    }
                },
                {
                    name: '二氧化碳浓度',
                    type: 'line',
                    //stack: '总量',
                    areaStyle: { normal: {} },
                    data: [23, 30, 20, 24, 25, 20, 15],
                    itemStyle: {
                        normal: {
                            color: '#3240d2'
                        }
                    },
                    markPoint: {
                        data: [
                            { type: 'max', name: '最大值' },
                            { type: 'min', name: '最小值' }
                        ]
                    },
                    markLine: {
                        data: [
                            { type: 'average', name: '平均值' }
                        ]
                    }
                },
                {
                    name: '氨气浓度',
                    type: 'line',
                    //stack: '总量',
                    areaStyle: { normal: {} },
                    data: [10, 9, 15, 14, 9, 12, 15],
                    itemStyle: {
                        normal: {
                            color: '#32c529'
                        }
                    },
                    markPoint: {
                        data: [
                            { type: 'max', name: '最大值' },
                            { type: 'min', name: '最小值' }
                        ]
                    },
                    markLine: {
                        data: [
                            { type: 'average', name: '平均值' }
                        ]
                    }
                },
                {
                    name: '硫化氢浓度',
                    type: 'line',
                    //stack: '总量',
                    areaStyle: { normal: {} },
                    data: [0.5, 1, 0.2, 0.1, 0.2, 0.1, 0.5],
                    itemStyle: {
                        normal: {
                            color: '#162542'
                        }
                    },
                    markPoint: {
                        data: [
                            { type: 'max', name: '最大值' },
                            { type: 'min', name: '最小值' }
                        ]
                    },
                    markLine: {
                        data: [
                            { type: 'average', name: '平均值' }
                        ]
                    }
                }
            ]
        };
        echartsA.setOption(option);
    }
}